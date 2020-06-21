/**
 * Compile 对象封装 - 负责模板解析
 * 	el:指定要解析的节点范围，选择器传入
 * 	vm:完成模板解析的vm驱动对象
 */
//构造函数
function Compile(el,vm){
	//注册VM驱动对象
	this.$vm = vm;

	//保存el ,数据检验规则：如果是一个ElementNode就el,不是就看天由命，退一步用CSS选择器来重新查询
	this.$el = this.isElementNode(el)?el:document.querySelector(el);

	//如果元素节点有效
	if(this.$el){
		//建立本对象的文档碎片
		this.$fragment = this.node2Fragment(this.$el)；

		//对文档碎片里的节点进行解析
		this.init();

		//完成解析后的文档碎片返回给该节点(appendChild先将父节点移除，然后添加到fragment中去)
		this.$el.appendChild(this.$fragment);
	}

}
//对象方法
Compile.prototype = {
	/*
	方法：判断是不是一个元素节点
	 */
	isElementNode:(el)=>{

	},
	/*
	方法：将节点转为文档碎片
	 */
	node2Fragment:(el)=>{
		//创建文档碎片对象  和 ?????
		let fragment = document.createDocumentFragment(),child;

		//通过while的特殊方式来移除el的各种节点
		while(child=el.firstChild){
			fragment.appendChild(child);
		}

		return fragment;
	},
	/*
	方法：Compile对象的初始化方法
	 */
	init:()=>{
		this.CompileElements(this.$fragment);//目前只有这个工作
	},
	/*
	方法：对本对象的$fragment属性完成解析
	 */
	CompileElements:(el)=>{
		//取出所有的节点 + 保存当前上下文对象
		let childNodes = el.childNodes,me = this;

		//通过伪数组转真数组的方式遍历每一个节点：
		[].slice.call(childNodes).forEach((node)=>{
			let text = node.textContent;	//获取节点的内容值,后面正则测试用的
			let Reg = /\{\{(.*)\}\}/;	//大括号{{...}}的识别正则表达

			//如果是元素节点，就编译元素里面的各种指令
			if(me.isElementNode(node)){
				me.compile(node);

			//如果是文本节点且该节点还有大括号，就解析该节点的
			}else if (me.isTextNode(node)&&reg.test(text)){
				me.compileText(node,RegExp.$1);
			}

			//看看是不是还有子节点，是就递归遍历
			if(node.childNodes && node.childNodes.length){
				me.CompileElements(node);
			}
		})
	},
	/*
	方法：元素指令解析
	 */
	compile:(node)=>{
		//保存下该节点的所有属性值的伪数组
		let nodeAttrs = node.attributes,me = this

		//遍历每一个属性值，如v-on:click:show()
		[].slice.call(nodeAttrs).forEach((attr)=>{
			//保存好属性名,如 v-on:click
			let attrName = attr.attrName

			//数据检验：是不是指令属性
			if(me.isDirective(attrName)){
				//保存属性值，如:show
				let exp = attr.value
				//从第3个位置开始截取属性名，如v-on:click:  => on:click
				let dir = attrName.substring(2);

				//如果是事件指令
				if(me.isEventDirective(dir)){
					//调用编译工具绑定事件
					compileUtil.eventHandler(node,me.$vm,exp,dir);
				}else{
					//如果是普通指令,如dir=v-if/v-for/v-bind
					compileUtil[dir] && compileUtil[dir](node,me.$vm,exp);
				}

				//完成一些指令之后，就可以移除vue的特殊属性恢复现场了
				node.removeAttribute(attrName);
			}
		})
	},
	/*
	方法：
	 */
	isTextNode:()=>{

	},
	/*
	方法：如果是文本节点且该节点还有大括号，就解析该节点
	 */
	compileText:(node,exp)=>{
		//通过一个统一的compileUtil翻译工具对象来将解析
		comileUtil.text(node,this.$vm,exp);
	},
	/*
	方法：根据属性值判断是不是以个合格的指令属性
	 */
	isDirective(attr){
		//根据字符查找第一个，返回索引值，找不到为-1，第2个参数是开始位置
		return att.indexOf('v-')==0;
	},
	/*
	方法：判断是不是一个事件指令
	 */
	isEventDirective(dir){
		return dir.indexOf('on')==0;
	}
}

/**
 * [compileUtil 一个统一的编译工具]
 * @type {Object}
 */
var compileUtil = {
	//v-text/text处理方法：
	text:(node,vm,exp)=>{
		//调用本对象的bind方法，多加传一个字符串进行待会拼凑
		this.bind(node,vm,exp,'text');
	},
	//v-html
	html:(node,vm,exp)=>{
		this.bind(node,vm,exp,'html');
	},
	//v-model数据绑定
	model:(node,vm,exp)=>{
		this.bind(node,vm,exp,'model');

		//保存本编译工具对象，还有根据exp属性名表达式取出vm中的的属性值
		let me = this,
			val = this._getVMVal(vm,exp);

		//给当前input节点添加输入监听
		node.addEventListener('input',(e)=>{
			var newValue = e.target.value;//拿到本时刻的值
			if(val === newValue){return}//没改变就啥也不要动
			me._setVMVal(vm,exp,newValue);
			val = newValue;

		})
	},
	//v-class
	class:(node,vm,exp)=>{
		this.bind(node,vm,exp,'class');
	},
	//v-if/v-......
	/*
	方法：bind是给每个指令不同的方式对应不同的解析界面的方式，
		并且，每个这样的bind,都会顺便新建一个监工 Watcher 方便我们以后调用修改界面数据
	 */
	bind:(node,vm,exp,dir)=>{
		//新建一个更新数据的函数,将自定义好的一个函数返回给它。自定义函数是通过刚刚传进来的text/...来识别
		var updataFn = updater[dir+'Updater'];

		//数据检验，执行函数
		updataFn && updataFn(node,this._getVMVal(vm,exp));

		//顺便新建一个监工 Watcher 方便我们以后调用修改界面数据(这里用了闭包，对每个node相关的值自动进行保留)
		new Watcher(vm,exp,(value,oldvalue)=>{
			//数据检验，执行函数
			updataFn && updataFn(node,value,oldvalue);
		})
	},
	/*
	方法：根据属性名来匹配指令，从methods中将回调函数拿下来，通过addEventListener来监听事件
	 */

	eventHandler:(node,vm,exp,dir)=>{
		//获取指令的类型 如on:click中的click
		let eventType = dir.split(':')[1];
			//根据exp如show读vm中methods中的函数，存为fn
			fn = vm.$options.methods && vm.$options.methods[exp];

		//数据检验：指令方法名，回调函数都存在的话,添加监听事件（回调函数加到vm驱动中执行）
		if(eventType && fn){
			node.addEventListener(eventType,fn.bind(vm),false);
		}
	},


	/*
	方法：根据vm对象 表达式 返回vm对象中的变量（之所以不直接用vm.xxx，因为可能复式变量表达式xxx.xxx.xxx）
	 */
	_getVMVal:(vm,exp)=>{
		let val = vm._data;
		exp = exp.split('.');
		exp.forEach((k)=>{
			val = val[k]
		})
		return val;
	},
	/*
	方法：更新Value值
	 */
	_setVMVal:(vm,exp,newValue)=>{

	}
}

/**
 * 新建一个可以根据不同节点更新数据的函数对象容器
 */
var updata = {
	//text节点的更新方法
	textUpdatar:(node,value)=>{
		//如果value是没定义的，就不写undefined了，直接''(把undefined输出很难看)
		node.textContent = typeof value == 'undefined'? '' : value;
	},
	//标签节点的更新方法
	htmlUpdater:(node,value)=>{
		node.innerHTML = typeof value == 'undefined'?'':value;
	},
	//class节点的更新方法
	classUpdatar:(node,value,oldvalue)=>{
		//先保存静态类名，如 aaa bbb  
		let className = node.className;
		//将静态类名与新类名合并： aaa bbb value/value
		node.className = className + className? ' ':'' + value;
	},
	/*
	model的数据绑定的更新方法
	 */
	model:(node,value,oldvalue)=>{
		node.value = typeof value == 'undefined'?'':value;
	}
}
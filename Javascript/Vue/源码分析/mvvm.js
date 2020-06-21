

/*
MVVM构造函数
 */
function MVVM(options){

	/*
	数据代理逻辑实现
	 */
	//保存配置
	this.$options = options;
	//拿出data
	let data = this._data = this.$options.data;
	//暂存this为me
	me = this;
	//遍历data，先照搬一下属性名,每一个都执行赋予代理
	Object.keys(data).forEach((key)=>{
		me.__proxy(key);
	})


	/*
	数据绑定注册
		将vm中的data和本身的对象传参进去
	 */
	observe(data,this);

	/*
	模板解析逻辑实现
		指定了el，就el,没指定，就整个body
	 */
	this.$compil = new Compile(options.el||document.body,this)
}


/**
 * MVVM的原型方法
 */

MVVM.prototype = {
	/*
	给每一属性定制代理的方法-数据代理
	 */
	__proxy:(key)=>{
		//采用描述属性的方法添加到本对象的属性
		Object.defineProperty(me,key,{
			enumerable:true,//允许遍历
			//为了 vm.xxx  能够读到刚刚定义的data数据，   实现代理读操作
			get:function proxyGetter(){
				return me._data[key];
			},
			//为了 vm.xxx=newVal  能够读到刚刚定义的data数据，   实现代理读操作
			set:function proxySetter(newVal){
				me._data[key] = newVal;
			}
		})
	}
}



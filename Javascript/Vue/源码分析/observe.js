/**
 * observe 数据绑定 - 逻辑实现
 */
//数据绑定入口检查函数
function observe(data,vm){
	//数据检验：必须不能为空，且还得是object
	if(!data||typeof data!== 'object'){
		return;
	}
	return new Observer(data);
}
/*
Observer对象 - 构造函数
 */
function Observer(data){
	//保存data为本对象
	this.data = data;
	//开启对data的监听入口
	this.walk(data);
}
/*
Observer对象 - 原型方法
 */
Observer.prototype = {
	/*
	开启对data的监听入口
	 */
	walk:(data)=>{
		//先保存好Observer为me
		let me = this;

		//遍历data的属性名
		Object.keys(data).forEach((key)=>{

			//对属性名已经属性值进行get/set注册 - 响应式数据绑定
			me.defineReactive(this.data,key,data[key]);
		})
	},
	/*
	方法：定制响应式数据绑定的核心代码
	 */
	defineReactive:(data,key,val)=>{
		//规定每一个数据都要有一个Dependency,所以在注册get/set之前，先新建一个Dep对象
		let dep = new Dep(),
			childObj = Observe(val); //预防 data:{name:{age}}嵌套数据变量，这里递归子数据进去

		//重新写data的属性，将其升级为带get/set的可以智能更新的属性
		Object.defineProperty(data,key,{
			enumerable:true, //可枚举
			configurable:false, //不可更改
			get:()=>{
				//建立Dep与Watcher的关系
				// 1.等会监工建立的时候会回来调用数据出发get，】
				// 	会将Dep.target指定，一旦指定，立刻就建立关系depend()
				if(Dep.target){
					dep.depend();
				}
				return val;
			},
			set:(newval)=>{
				//如果变量没变，就兴师动众去更改了
				if(newval===val){return}

				val = newval;

				//新的值也要重新注册observe
				childObj = observe(newval);

				//通知相关的订阅者
				dep.notify();
			}
		})
	}

}
/*
Dep 对象 - 构造函数
 */

//全局变量 Depid生成记录器
var uid = 0;

function Dep(){
	//不重复的方式生成以个dep.id
	this.id = uid++;

	//订阅者名单，写着监工Watcher的this指针，一个data数据一份这样的名单，
	//一旦发生改变，就可以触发订阅者干活更新界面数据
	this.subs = [];


}
/*
Dep 对象 - 原型方法
 */
Dep.prototype = {
	/*
	方法：建立Dep 与 Watcher的关系
	 */
	depend:()=>{
		//由于监工在调用this.get时Dep指定了target为这个监工，故直接
		//	监工.addDep(当前数据对应的Dep)  - 由此建立两者关系
		Dep.target.addDep(this);
	},
	/*
	方法：通知相关订阅者
	 */
	notify:()=>{
		//通知所有订阅者 - Watcher,逐一更新数据
		this.subs.forEach((sub)=>{
			//每个sub都是记录着每一个Watcher的this指针，故不需担心错乱
			//不需担心那些不变的数据，因为监工们有this.value做新旧变量对比
			sub.update();
		})
	},
	/*
	方法：添加Watcher到Dep中
	 */
	addSub:(sub)=>{
		this.subs.push(sub);
	}
	
}

//所有的Dep对象的原型只有一个共同的属性
//用来记录当前要建立关系的监工
//全局变量
Dep.target = null;


/*
Watcher对象 - 构造函数
	vm:vm驱动对象
	exp:界面上的表达式，如name 
	cb:对应name的updatar的回调函数
 */
function Watcher(vm,exp,cb){
	//保存属性
	this.vm = vm;
	this.exp = exp;
	this.cb = cb;

	//构造一个记录Dep依赖对象的容器,以对象的形式,为了后面能够判断是否已经存在该属性的hasOwnProperty利用
	this.depIds = {}；

	//虽说它是数据的监督者，但是也要保存当前数据的值呀,为了就是开启run时新旧对比逻辑
	this.value = this.get();
}
/*
Watcher对象 - 原型方法
 */
Watcher.prototype = {
	/*
	方法：当前Watcher的工作函数，进行界面的数据更改
	 */
	update:()=>{
		this.run();
	},
	/*
	方法：监工的本职工作
	 */
	run:()=>{
		//调用本对象的获取最新数据的方法获得最新数据
		let value = this.get();

		//记得之前保存下来的value值作为旧数据
		let oldVal = this.value;

		//之所以新旧对比，就是预防变量不变我不必兴师动众
		if(value!==oldVal){
			//更换本对象的临时数据
			this.value = value

			//以本在本对象注册的vm驱动对象调用对应本对象的updatar的回调函数，进行界面更新数据,
			//传oldVal是为了统一，因为class的界面updater方法需要
			this.cb.call(this.vm,value,oldVal);
		}
	},
	/*
	方法：本对象的获取最新数据的方法获得最新数据
	 */
	get:()=>{
		//定Dep的服务对象为当前监工
		Dep.target = this;

		//调用本对象的getVMVal方法来获得value值
		let value = this.getVMVal();

		//定Dep的服务对象为空
		Dep.target = null;
	},
	/*
	方法：添加dep依赖，建立之间的关系
	 */
	addDep:(dep)=>{
		//数据检验：如果已经存在了就不建立了，规定不能重复建立关系
		if(!this.depIds.hasOwnProperty(dep.id)){
			//dep方先添加本Watcher  通过注册到dep，成为订阅者，就可以被dep调用->Watcher更新
			dep.addSub(this);

			//我方Watcher 添加dep方  也为了后面不重复建立关系
			this.depIds[dep.id] = dep;
		}
	},
	/*
	方法：直接从vm驱动，获得表达式里的值
	 */
	getVMVal:()=>{
		let exp = this.exp.split('.');
		let val = this.vm._data;
		exp.forEach((key)=>{
			val = val[key]; //这一句会触发指定数据中的get方法
		})
		return val;
	}
}
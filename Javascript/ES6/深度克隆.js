
function checkedType(target){
	return Object.prototype.toString.call(target).slice(8,-1);
}
function clone(target){
	//判断类型，顺便初始化一个准备返回的res
	let targetType = checkedType(target),
		result;

	//如果是数组/对象，就重新定义个一个空地址 
	if('Object'=== targetType){
		result = {};
	}else if ('Array' === targetType){
		result = [];
	}else{
		//不是数组，不是对象，就可以直接返回了
		return target;
	}

	//针对数组、对象，重新遍历键值对
	for(let i in target){
		//获得数组/对象的每一项 键值对 的 值
		let value = target[i]

		if(checkedType(value) === 'Object'||checkedType(value)=== 'Array'){
			//如果该值又是一个数组/对象  直接递归
			result[i] = clone(value);
		}else{
			//不是的话，直接 等号赋值
			result[i] = value;
		}
	}

	return result;
}
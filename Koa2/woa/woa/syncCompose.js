function add(x,y){
	return x+y
}

function double(z){
	return z*2
}


const middlewares = [add,double]
let len = middlewares.length
function compose(midds){
	return (...args)=>{
		//初始值
		let res = midds[0](...args)
		for(let i=1;i<len;i++){
			res = midds[i](res)
		}
		return res
	}
}
const fn = compose(middlewares)
const res = fn(1,2)
console.log(res)
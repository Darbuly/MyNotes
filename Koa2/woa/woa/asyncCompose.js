//同步
async function fn1(next){
	console.log('fn1')
	await next()
	console.log('end fn1')
}

//延迟的异步
async function fn2(next){
	console.log('fn2')
	await delay()
	await next()
	console.log('end fn2')
}

async function fn3(next){
	console.log('fn3')
}

function  delay(){
	return new Promise((resolve,reject)=>{
		setTimeout(()=>{
			resolve()
		},2000)
	})
}

//要实现fn1->fn2->2000ms->fn3->end fn2->end fn1
//


function compose(middlewares){
	return function(){
		return dispatch(0)

		function dispatch(i){
			let fn = middlewares[i]
			if(!fn){
				return Promise.resolve()
			}
			return Promise.resolve(fn(function next(){
				return dispatch(i+1)
				//fn1(fn2(fn3))但是都是以promise对象返回的
			}))
		}
	}
}
const middlewares = [fn1,fn2,fn3]
const finalFn = compose(middlewares)
finalFn()
const http = require('http')

let request = {
	get url(){
		return this.req.url
	}
}
let response = {
	get body(){
		return this._body
	},
	set body(val){
		this._body = val
	}
}

let context = {
	get url(){
		return this.request.url
	},
	get body(){
		return this.response.body
	},
	set body(val){
		this.response.body = val
	}
}


class Application{
	constructor(){
		//this.callback = ()=>{}//定义一个空函数
		this.context = context
		this.request = request
		this.response = response
		this.middlewares = []
	}
	use(callback){
		this.middlewares.push(callback)
	}
	listen(...args){
		const server = http.createServer(async(req,res)=>{
			let ctx = this.createCtx(req,res)
			// await this.callback(ctx)
			const fn = this.compose(this.middlewares)
			await fn(ctx)
			ctx.res.end(ctx.body)
		})
		server.listen(...args)//将10行传进来的所有的参数直接传到这里来就行了
	}
	createCtx(req,res){
		let ctx = Object.create(this.context)
		ctx.request = Object.create(this.request)
		ctx.response = Object.create(this.response)
		ctx.req = ctx.request.req = req//将原生的req挂载到我们模拟的req上
		ctx.res = ctx.response.res = res
		return ctx
	}
	compose(middlewares){
	return function(context){
		return dispatch(0)

		function dispatch(i){
			let fn = middlewares[i]
			if(!fn){
				return Promise.resolve()
			}
			return Promise.resolve(fn(context,function next(){
				return dispatch(i+1)
			}))
		}
	}
}
}

//对外暴露

module.exports = Application
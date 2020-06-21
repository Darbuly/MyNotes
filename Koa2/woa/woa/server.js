
const Woa = require('./application')

const app = new Woa()


function  delay(){
	return new Promise((resolve,reject)=>{
		setTimeout(()=>{
			resolve()
		},2000)
	})
}


app.use(async (ctx,next)=>{
	ctx.body = '1'
	await next()
	ctx.body += '2'
})
app.use(async (ctx,next)=>{
	ctx.body += '3'
	await delay()
	await next()
	ctx.body += '4'
})
app.use(async (ctx,next)=>{
	ctx.body += '5'
})

app.listen(3344,()=>{
	console.log(`server runing on port 3344`)
})





// const Woa = require('./application')

// const app = new Woa()

// app.use((req,res)=>{
// 	res.writeHead(200)
// 	res.end('hello Dbl')
// })

// app.listen(3344,()=>{
// 	console.log(`server runing on port 3344`)
// })














// //引入nodejs自带的http工具
// const http = require('http')
// // 新建一个http协议
// const server = http.createServer((req,res)=>{
// 	res.writeHead(200)
// 	res.end('hello Dbl!')
// })
// // 监听3344端口
// server.listen(3344,()=>{
// 	console.log('server start on port 9092')
// })


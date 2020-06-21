



//创建可读流
var rs = fs.createReadStream("a.mp3")
//
//创建可写流
var ws = fs.reateWriteStream("b.mp3")
//
//监听打开
rs.once("open",()=>{
	console.log("可读流打开")
})
ws.once("open",()=>{
	console.log("可写流打开")
})
//监听关闭
rs.once("close",()=>{
	console.log("可读流关闭")
	ws.end()
})
ws.once("close",()=>{
	console.log("可写流关闭")
})
//
//
//写数据
rs.on("data",(data)=>{
	ws.write(data)
})


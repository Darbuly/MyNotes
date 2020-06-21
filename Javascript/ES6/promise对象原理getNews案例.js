
function getNews(url){
	let promise = new Promise((resolve,reject)=>{
		//状态：初始化pedding
		//执行异步任务
		//创建xmlHttp对象
		let xmlHttp = new XMLHttpRequest();
		xmlHttp.onreadystatechange = function(){
			if(xmlHttp.readStayle===4){
				if(xmlHttp.status==200){
						resolve(xmlHttp.resonseText);
					}else{
						reject("没有获得内容")
					}
			}
		}
		xmlHttp.open('Get',url)
		xmlHttp.send()
	})
	return promise
}

getNews("xxxxxx新闻url")
	.then((data)=>{
		//请求成功
		console.log(data)
		let commentUrl = JSON.parse(data).commentUrl
		//发送请求获得评论
		return getNews(commentUrl)
	},(error)=>{
		//请求失败
		console.log(error)
	})
	.then((data)=>{
		//评论的请求成功！
	},(error)=>{
		//评论的请求失败！
	})
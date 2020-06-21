# 1. AJAX概述 #
面试官如果问：“什么是AJAX？”  答：  
AJAX = Asynchronous JavaScript And XML  
一句话：**异步的 JavaScript 和 XML**   
AJAX **不是编程语言**，而是现有标准的新方法。  
AJAX **是一门艺术**（如何实现在不重新加载整个页面的情况下，与服务器交换数据并更新部分网页一种艺术）。

# 2. 历史 #
> 通过了解它的历史，我们可以更加全面理解AJAX。（形成我们手撕面试官的宏大思维）  

有时候，当您在谷歌的搜索框输入关键字时，JavaScript 会把这些字符发送到服务器，然后服务器会返回一个搜索建议的列表。Google Suggest 使用 AJAX 创造出这样的动态界面，所以  
在 2005 年，Google 通过其 Google Suggest 使 AJAX 变得流行起来。

# 3. XMLHttpRequest对象(XHR)是AJAX的基础 #
## 3.1 语法   ##
    variable=new XMLHttpRequest();  
> 兼容警告：  
> IE5 和IE6使用的是ActiveX对象：
> variable=new ActiveXObject("Microsoft.XMLHTTP");  
> 兼容写法如下：

    var xmlhttp;
    if (window.XMLHttpRequest)
      {//IE7+, Firefox, Chrome, Opera, Safari
      xmlhttp=new XMLHttpRequest();
      }
    else
      {//IE6, IE5
      xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
      }




## 3.2 XHR对象方法——请求 ##
    xmlhttp.open(method,url,async)
    xmlhttp.send(string);

规定请求的类型、URL 以及是否异步处理请求。




### 3.2.1 method ###
请求的类型；GET 或 POST(目前稳定支持这两个，关于REST规范里面的其他，有些不支持，故平时记住这俩够用了 REST规范详见[http://www.ruanyifeng.com/blog/2011/09/restful.html](http://www.ruanyifeng.com/blog/2011/09/restful.html "理解RESTful架构-阮一峰网络日志"))  
#### 3.2.1.1 GET/POST选择规范 ####
**结论1：动机规范，“获取GET，上传POST”**  
get重点在从服务器上获取资源，post重点在向服务器发送、上传数据；  

**结论2：置于url的是GET，可见不安全，封存的是POST，不可见较安全**  
get传输数据是通过URL请求，以field（字段）= value的形式，置于URL后，并用”?”连接，多个请求数据间用”&”连接，如http://127.0.0.1/Test/login.action?name=admin&password=admin，这个过程用户是**可见的**；  

get是不安全的，因为URL是可见的，可能会泄露私密信息，如密码等(页面可以被缓存，或者获得历史访问记录)；  
post传输数据通过Http的post机制，将字段与对应值封存在请求实体中发送给服务器，这个过程对普通用户是**不可见的**(懂抓包的除外)；post较get安全性较高；  

**结论3：Get高效率有限制，POST低效率限制小**  
Get效率较高，但因为受URL长度限制(其实是浏览器决定这个长度的)，故传输的数据量小。
Post可以传输大量数据，所以上传文件时只能用Post方式；

**结论4：GET不喜欢中文**  
get方式只能支持ASCII字符，向服务器传的中文字符可能会乱码（你会发现有很多%）。
post支持标准字符集（UFT-8\GBK等..），可以正确传递中文字符。


### 3.2.2 url ###
通过统一资源定位符定位文件在服务器上的位置
### 3.2.3 async ###
true（异步）或 false（同步）  

- async=true  
XMLHttpRequest 对象如果要用于 AJAX 的话，其` open() `方法的 async 参数必须设置为 true，且必须规定在响应处于`XMLHttp.onreadystatechange`事件中的就绪状态时执行的回调函数。  
- async=false  
一般很少使用，但是对于一些小型的请求，能接受JavaScript 会等到服务器响应就绪才继续执行下面代码的情况就可以使用。否则如果服务器繁忙或缓慢，应用程序会挂起或停止。  
注意：当您使用 async=false 时，请不要编写 `onreadystatechange `函数，而是把代码放到 send() 语句的后面，相当于后面的执行就是所谓的“回调”函数了。
### 3.2.4 string ###
如果需要像 HTML 表单那样 POST 数据，请先使用` setRequestHeader()` 来添加 HTTP 头。然后在 send() 方法中规定您希望发送的数据。 如果发送的是表单数据格式的话，服务器端可以向字符串一样地解析。

"name=value&anothername="+encodeURIComponent(myVar)+"&so=on"
`setRequestHeader(header,value) `向请求添加 HTTP 头。  


- header: 规定头的名称
- value: 规定头的值
## 3.3 AJAX - 服务器响应 ##
### 3.3.1 读取响应数据实体 ###


- responseText属性
获得字符串形式的响应数据。可以直接用在DOM元素节点中的`innerHtml`  ,如：
`document.getElementById("myDiv").innerHTML=xmlhttp.responseText;`  


- responseXML属性
获得 XML 形式的响应数据。
### 3.3.1 读取响应数据HEAD ###


- getResponseHeader(ByteString)方法
返回包含指定头文本的字符串，ByteString参数表示要返回文本值的标题的名称。


- XMLHttpRequest.getAllResponseHeaders() 方法返回所有的响应头，以 回车符（CR）和换行符（LF）即`\r\n`分割的字符串，或者 null 如果没有收到任何响应。
## 3.4  XMLHttpRequest对象的三个重要的响应属性 ##
### 3.4.1 readyState ###
存有 XMLHttpRequest 的状态。从 0 到 4 发生变化。  

- 0: 请求未初始化  
- 1: 服务器连接已建立
- 2: 请求已接收
- 3: 请求处理中
- 4: 请求已完成，且响应已就绪
### 3.4.2 onreadystatechange ###
存储一个回调函数（或函数名），每当 readyState 属性改变时，就会调用该函数。对应着 readyState 的每个变化，onreadystatechange事件被触发 5 次（0 - 4）。
### 3.4.3 status ###
常见状态码总结[https://blog.csdn.net/Darbuly/article/details/105596216](https://blog.csdn.net/Darbuly/article/details/105596216 "简记-常见HTTP状态码生存手册-300字")


# 4. HelloWorld挑战 #
## 4.1 手写一个GET请求 ##
> 需求：
> 假设某个服务器上的一个helloAjax.html资源定位为：“/serve/helloAjax.html”，请用GET的方法去请求之，并console.log输出它。
> 要求兼容浏览器

    var xmlhttp;
    if (window.XMLHttpRequest) {
      xmlhttp=new XMLHttpRequest();
    }
    else{
      xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
    }

    if (!xmlhttp) {
      alert('放弃吧，你玩不了AJAX!');
      return false;
    }
    xmlhttp.onreadystatechange = ()=>{
	    if (xmlhttp.readyState === 4) {
	      if (xmlhttp.status === 200) {
	        console.log(xmlhttp.responseText);
	      } else {
	        alert('There was a problem with the request.');
	      }
	    }
	};
    xmlhttp.open('GET', “/serve/helloAjax.html”);
    xmlhttp.send();
    
## 4.2 手写一个POST请求 ##
> 需求：
> 假设某个input标签下的一个id属性为username,请用Javascript获取它的内容。
> 假设某个服务器上的一个test.php资源定位为：“/serve/test.php”，返回的数据为  
> {"username":"Make","String":"HelloAjax!"}  
> 请用POST的方法去请求之，并console.log输出String。
> 要求兼容浏览器

    var xmlhttp;
    if (window.XMLHttpRequest) {
      xmlhttp=new XMLHttpRequest();
    }
    else{
      xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
    }

    if (!xmlhttp) {
      alert('放弃吧，你玩不了AJAX!');
      return false;
    }
    xmlhttp.onreadystatechange = ()=>{
	    if (xmlhttp.readyState === 4) {
	      if (xmlhttp.status === 200) {
	        var response = JSON.parse(xmlhttp.responseText);
			console.log(response.String)
	      } else {
	        alert('There was a problem with the request.');
	      }
	    }
	};
    xmlhttp.open('POST', “/serve/test.php”);
    xmlhttp.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
	var userName = document.getElementById('username').value
    xmlhttp.send('userName=' + encodeURIComponent(userName));
总结5：ajax请求最重要的8个方法

- new XMLHttpRequest()
- .onreadystatechange()
- .state === 4
- .status === 200
- .responseXXXX
- .open
- .setRequestHeader
- .send
## 4.3 结合promise封装一个ajax请求 ##
> 需求：
> 用回调最大的问题是回调函数没有命名规范，每个开发者都有自己的命名规范，一旦在项目中如果引用了多个库，各个库之间的ajax回调函数可能会互相影响，Promise结合箭头函数的出现正好解决了这个问题,通过promise，可以不需要考虑命名规范。
> 所以，请用promise来封装一个ajax请求。  
> 

    Pajax = function(url,method,body,headers){
    	return new Promise(function(resolve,reject){    
		    var xmlhttp;
		    if (window.XMLHttpRequest) {
		      xmlhttp=new XMLHttpRequest();
		    }
		    else{
		      xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
		    }
		
		    if (!xmlhttp) {
		     	reject.call(uncefined,“放弃吧！你玩不了AJAX!”)
		    }
	        for(let key in headers){
	            let value = headers[key]
	            xmlhttp.setRequestHeader(key,value)
	        }
	
	        xmlhttp.onreadtstatechange = function(){
	            if(xmlhttp.readystate === 4 ){
	                if(xmlhttp.status >= 200 && xmlhttp.status < 300 || xmlhttp.status === 304){
	                    resolve.call(undefined,xmlhttp)
	                }else if(request.status >=400){
	                    reject.call(uncefined,xmlhttp)
	                }
	            }
	        }
	        xhr.open(method,url)
	        request.send(body)
	    }    
    })
var Pajax = function(url,method,body,headers){
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
                    reject.call(undefined,xmlhttp)
                }
            }
        }
        xmlhttp.open(method,url)
        request.send(body)
    }    
}

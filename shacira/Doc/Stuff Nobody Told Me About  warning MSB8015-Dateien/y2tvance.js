(function(){try{if(typeof YontooClient!="undefined"&&YontooClient.trafficVanceUrl){var f=typeof localStorage!="undefined",c=!1,e=function(b,d,c,f){try{var a=document.createElement("script");a.type="text/javascript";a.src=b;var e=!1;if(c)a.id=c;if(f==!0)a.async=!0;a.onload=a.onreadystatechange=function(){if(!e&&(!this.readyState||this.readyState==="loaded"||this.readyState==="complete"))e=!0,typeof d=="function"&&d(),a.onload=a.onreadystatechange=null,a.parentNode.removeChild(a)};document.getElementsByTagName("head")[0].appendChild(a)}catch(g){}};
YontooClient.loadTrafficVance=function(b){try{if(!c&&(c=!0,b)){for(var d,b=""+b;b.length<5;)b="0"+b;d=b=b.slice(-5);e(YontooClient.trafficVanceUrl+d,null,"confsc",!0);f&&localStorage.setItem("eitvrubid",d)}}catch(g){}};YontooClient.bid!=null?YontooClient.loadTrafficVance(YontooClient.bid):f&&localStorage.getItem("eitvrubid")?YontooClient.loadTrafficVance(localStorage.getItem("eitvrubid")):e("http://service.blankbase.com/GetRubiconGuid/"+YontooClient.getInstallId()+"/YontooClient.loadTrafficVance");
setTimeout(function(){c||YontooClient.loadTrafficVance(-1)},1E3)}}catch(g){}})();
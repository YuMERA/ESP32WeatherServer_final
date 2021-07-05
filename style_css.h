const char style_css[] PROGMEM = R"=====(* {padding: 0; margin: 0;}
body {font-family: Helvetica, sans-serif;font-size: 13px;}
.container {margin: auto; width: 93%; border: 1px solid gray; background-color:white;}
.container h2, h3 {margin: 5px;}
header {color: white; background-color: black; text-align: center; height: auto; padding: 5px; clear:left;}
article {margin-left: 270px; border-left: 1px solid gray; padding: 1em; overflow: hidden;}

article table {font-size: 15px; width: 75%; margin-left: auto; margin-right: auto; box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);}
article td, th {border: 1px solid #808080; text-align: left; padding: 6px;}
article th {padding-top: 10px; padding-bottom: 10px; text-align: center; background-color: #FCBC32; color: black;}
article tr:nth-child(even) {background-color: #f2f2f2;}
article tr:nth-child(odd) {background-color: white;}
footer {position:relative; background-color: black; text-align: center; padding: 3px; bottom: 3px; width: 93%; color: #eb6206;}
footer p{font-family: Helvetica, sans-serif; font-size: 10px; letter-spacing: .5px; color: whitesmoke; margin-top: 5px;}
article marquee {font-family: Helvetica ,Arial,sans-serif!important; font-size: 12px; color: black; margin: 5px 0 0 0;}
nav {float: left; max-width: 300px; margin:0; padding:1em; background-color:white;}
.klimerko {font-family: Helvetica, sans-serif; font-Size : 13px;}
.klimerko a {color: whitesmoke; text-decoration: none; font-weight: bold; border: 1px solid #fff; border-radius: 30px; margin: 8px 0px 0px 10px; padding: 3px 10px; background-color:#F36454; float: right;}
.klimerko a:hover {background: #4CAF50; transition: .4s;}
.trenutno-stanje {margin-top: 10px;}
.trenutno-stanje p {padding: 2px;}
.menu {list-style: none; margin: 0 0 5px 20px; text-align: left;}
.menu li {display: inline-block; margin: 15px 0 0 0;}
.menu li a {text-decoration: none; color: silver; padding: 3px 10px; letter-spacing: 1px; border-radius: 10px;}
.menu li a:hover {background: white; transition: .4s; color: #000;}
.widgets{ width: 270px; box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);}
.w-header{background-color: #FCBC32; color: black; padding: 10px; font-size: 14px; text-align: left;}
.w-header h3 {margin-bottom: 2px;}
.w-content{height: 130px; width: 270px;}
.left-w-content{height:150px; width: 130px; margin-top: 1rem;
                padding: 5px; 
                font-family: "Oswald", Arial, sans-serif; font-size: 52px; font-weight: 600;
                text-align: center; color: #333333;
                box-sizing: border-box;
                position: absolute;}
                
.right-w-content{left: 130px; height:150px; width: 140px; margin-top: 5px;
                 padding: 5px;
                 font-size: 12px; font-family: Helvetica ,Arial,sans-serif!important; color: #333; text-align: left;
                 line-height: 1;
                 box-sizing: border-box; position: relative;
                                }
.right-w-content td {padding: 1px;}
.w-footer{background-color: #FCBC32; color: black; padding: 5px; font-size: 14px; text-align: right;}

)=====";

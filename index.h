const char MAIN_page[] = R"=====(
<!DOCTYPE html>
<html>
<head>
<style>
body {
  background-color: black;
  color: white;
}
#clock {
   font-size: 40px;
   position: absolute;
   right: 0px;
   display: inline;
   font-family: Baskerville, Georgia;
}
.container {
  width: 400px;
  height: 200px;
  position: absolute;
  top: 10%;
  left: 50%;
  overflow: hidden;
  text-align: center;
}

.gauge-b {
  z-index: 4;
  position: absolute;
  background-color: #222;
  width: 250px;
  height: 125px;
  top: 75px;
  margin-left: 75px;
  margin-right: auto;
  border-radius: 250px 250px 0px 0px;
}

.gauge-c {
  z-index: 2;
  position: absolute;
  background-color: #5664F9;
  width: 400px;
  height: 200px;
  top: 200px;
  border-radius: 0px 0px 200px 200px;
  transform-origin: center top;
  transform: rotate(var(--deg));
}

.gauge-data {
  z-index: 4;
  color: rgba(255,255,255,1);
  font-size: 1.5em;
  line-height: 25px;
  position: absolute;
  width: 400px;
  height: 200px;
  top: 90px;

}

.button {
    background-color: #4CAF50;
  color: white;
  padding: 15px 32px;
  text-align: center;
  display: inline;
  font-size: 16px;
  margin: 21px 9px;
  cursor: pointer;
}
.numdis {
   font-family: "Times New Roman", Times, serif;
   display: inline;
   font-size: 40px;
   }
</style>
</head>
<body>
<span class="numdis" >time :</span> 
<span id="hour" class = "numdis" >0</span> : 
<span id="minute" class = "numdis" >0</span> : 
<span id="sec" class = "numdis" >0</span> 

<div id="clock"> </div>
<div id="demo">
 <p class="numdis">STEPS :</p>
 <p class="numdis" id="steps">1</p><br>
  <p class="numdis">DISTANCE :</p>
 <p class="numdis" id="distance">1</p><br>
</div>
<div class="container">
  <div class="gauge-b"></div>
  <div id="deg1" class="gauge-c"></div>
  <div class="gauge-data">
    <h1 id="percent">10</h1>
  </div>
</div>
<div id="demo">
  <button type="button" class="button" id="motor0" onclick="sendDat(1)">1</button>
  <button type="button" class="button" id="motor1" onclick="sendDat(2)">2</button>
</div>


<script>
function clock(){
//Save the times in variables
var today = new Date();
var hours = today.getHours();
var minutes = today.getMinutes();
var seconds = today.getSeconds();
//Set the AM or PM time

if (hours >= 12){
  meridiem = " PM";
}
else {
  meridiem = " AM";
}
//convert hours to 12 hour format and put 0 in front
if (hours>12){
  hours = hours - 12;
}
else if (hours===0){
  hours = 12; 
}
//Put 0 in front of single digit minutes and seconds
if (minutes<10){
  minutes = "0" + minutes;
}
else {
  minutes = minutes;
}

if (seconds<10){
  seconds = "0" + seconds;
}
else {
  seconds = seconds;
}
document.getElementById("clock").innerHTML = (hours + ":" + minutes + ":" + seconds + meridiem);
}
setInterval('clock()', 1000);

var timeElapsed = 0;
            var timerID = -1;
            function tick() {
                timeElapsed++
                document.getElementById("sec").innerHTML = timeElapsed % 60;
                document.getElementById("minute").innerHTML = Math.floor(timeElapsed / 60 ) % 60;
                document.getElementById("hour").innerHTML = Math.floor((timeElapsed % 86400 ) / 3600);
            }

            function start() {
                if(timerID == -1){
                    timerID = setInterval(tick, 10);
                }
            }

            function stop() {
                if(timerID != -1){
                    clearInterval(timerID)
                    timerID = -1
                }
            }

            function reset() {
                stop();
                timeElapsed = -1;
                tick()
            }
            
function sendDat(load) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      pdata(this);
    }
  };
  xhttp.open("GET", "setLoad?loadstate="+load, true);
  xhttp.send();
}
setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getData();
}, 1000);

function getData() {
  var xhttp = new XMLHttpRequest(); 
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      pdata(this);
    }
  };
  xhttp.open("GET", "getstatus", true);
  xhttp.send();
}
function pdata(xhttp) {
  var myObj = JSON.parse(xhttp.responseText);
   document.getElementById("steps").innerHTML = myObj.t0;  
   document.getElementById("percent").innerHTML = myObj.t2;  
   document.getElementById("distance").innerHTML = myObj.t1;
   document.getElementById('deg1').style.setProperty('--deg', myObj.t2 + 'deg');
   if (myObj.t3 == 0){
   reset()
   start()
   }
   if (myObj.t3 == 1){
   start()
   }
   if (myObj.t3 == 2){
   stop()
   }
   
}
</script>
</body>
</html> 
)=====";

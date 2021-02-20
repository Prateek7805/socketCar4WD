const char js[] PROGMEM = R"=====(
var Socket;
var wiFiMODE = 0;
document.addEventListener('DOMContentLoaded', init, false);
function init(){

  Socket = new WebSocket('ws://'+window.location.hostname+':81/');
  Socket.onmessage = function(event){
    console.log(event.data);
  }
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function(){
    if(this.readyState == 4 && this.status == 200){
      wiFiMODE = parseInt(this.responseText);
      doc("wiFiMODE").checked = (wiFiMODE == 0)? false : true;
    }
  }
  xhr.open("GET", "/hello", true);
  xhr.send();
}


function _send(head, data){
  Socket.send(head+data);
  console.log(head+data);
  }

function doc(id){
  return document.getElementById(id);
}

doc("wiFiMODE").addEventListener('click', function(){
  _send("W",(this.checked)?1:0);
});

doc('forward').addEventListener('touchstart', buttonPress);
doc('backward').addEventListener('touchstart', buttonPress);
doc('left').addEventListener('touchstart', buttonPress);
doc('right').addEventListener('touchstart', buttonPress);
doc('stop').addEventListener('touchstart', buttonPress);

doc('forward').addEventListener('mousedown', buttonPress);
doc('backward').addEventListener('mousedown', buttonPress);
doc('left').addEventListener('mousedown', buttonPress);
doc('right').addEventListener('mousedown', buttonPress);
doc('stop').addEventListener('mousedown', buttonPress);

function buttonPress(){
  _send(this.id[0], 1);
}

doc('forward').addEventListener('touchend', buttonRelease);
doc('backward').addEventListener('touchend', buttonRelease);
doc('left').addEventListener('touchend', buttonRelease);
doc('right').addEventListener('touchend', buttonRelease);
doc('stop').addEventListener('touchend', buttonRelease);

doc('forward').addEventListener('mouseup', buttonRelease);
doc('backward').addEventListener('mouseup', buttonRelease);
doc('left').addEventListener('mouseup', buttonRelease);
doc('right').addEventListener('mouseup', buttonRelease);
doc('stop').addEventListener('mouseup', buttonRelease);
document.addEventListener('mouseup', function(){
  _send('s', 0);
});

function buttonRelease(){
  _send(this.id[0], 0);
}

doc('range').addEventListener('input', function(){
  doc('rangeVal').innerHTML = this.value;
  _send('v', this.value);
});

)=====";
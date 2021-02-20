const char css[] PROGMEM = R"=====(
*{
  box-sizing: border-box;
  margin: 0;
  padding: 0;
  outline: none;
}

html{
  -webkit-user-select: none; /* Safari */
  -moz-user-select: none; /* Firefox */
  -ms-user-select: none; /* IE10+/Edge */
  user-select: none; /* Standard */
}

body{
  font-family: monospace, Calibri , sans-serif;
  background-color: #1a1a2e;
}
.d-ib{
  display:inline-block;
}
.w-25{
  width: 25%;
}
.w-50{
  width:50%;
}
.title{
  font-size: 30px;
  font-weight: bold;
}
.f-right{
  float:right;
}
.center{
  display: table;
  margin-left: auto;
  margin-right: auto;
}
.generalWhite{
  color: #fff;
}
.generalWidth{
  width: 80%;
}
.generalButton{
  background-color: #fff;
  padding:20px;
  margin: 10px;
  border: none;
  border-radius: 5px;
  transition-duration: 150ms;
  transition-property: transform;
  transition-timing-function: ease-in-out;
}

.generalButton:active{
  transform:scale(0.97);
}

.generalButtonCircle{
  background-color: #fff;
  margin-top: 20px;
  border: none;
  border-radius: 50%;
  transition-duration: 150ms;
  transition-property: transform;
  transition-timing-function: ease-in-out;
}

.generalButtonCircle:active{
  transform:scale(0.97);
}

.generalRange {
  -webkit-appearance: none;
  width: 90%;
  height: 10px;
  border-radius: 5px;
  background: #d3d3d3;
  outline: none;
  opacity: 0.7;
  -webkit-transition: .2s;
  transition: opacity .2s;
}

.generalRange:hover {
  opacity: 1;
}

.generalRange::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  background-color: #a2f371;
  width: 20px;
  height: 20px;
  border-radius: 50%;
  cursor: pointer;
  border: none;
}

.generalRange::-moz-range-thumb {
  width: 20px;
  height: 20px;
  background-color: #a2f371;
  border-radius: 50%;
  cursor: pointer;
  border: none;
}

.container{
  width: 100%;
}
.header{
  margin-top: 10px;
 background-color: #03c4a1;
 border: none;
 border-radius: 4px;
}
.content{
  width : 80%;
}



.range{
  margin-top: 20px;
  width: 45%;
}
#rangeVal{
  margin-left: 10px;
}

.switch {
  position: relative;
  display: inline-block;
  width: 70px;
  height: 30px;
}

.switch input {
 display: none;
}

.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #2196F3;
  transition: 0.4s;
}

.slider:before {
  position: absolute;
  content: "";
  height: 24px;
  width: 26px;
  left: 4px;
  bottom: 3px;
  background-color: #FFF;
  transition: .4s;
}

input:checked + .slider {
  background-color: #ABDF61;
}

input:focus + .slider {
  box-shadow: 0 0 10px #2196F3;
}

input:checked + .slider:before {
  transform: translateX(36px);
}

/* Rounded sliders */
.slider.round {
  border-radius: 32px;
}

.slider.round:before {
  border-radius: 50%;
}

@media(max-width: 767px) and (min-width: 500px){
  .range{
    width: 60%;
  }
}

@media(max-width: 499px){
  .range{
    width: 80%;
  }
  .generalRange{
    width: 70%
  }
}

)=====";
var P = 0,
    I = 0,
    D = 0,
    previous_error = 0,
    Kp = 1,
    Ki = 0.2,
    Kd = 2,
    MOVE_FWD = 230;


function PID(error)
{
  P = error; // Proportional = Robot position
  I += error; // Integral = Graph Area
  D = error - previous_error; // Derivative = Error Variation (Delta ERROR)
  
  previous_error = error;
  return (Kp*P) + (Ki*I) + (Kd*D);
}

function LineCompare(colors, other)
{
  var lines = colors.split('');
  var values = other.split('');
  var result = true;

  for(var i = 0; i < 5 && result == true; i++)
  {
    if(values[i] == '0' || values[i] == '1')
      result = values[i] == lines[i];
  }

  return result;
}

function CalculateError(colors)
{
       if(LineCompare(colors, "11110")) return 4;
  else if(LineCompare(colors, "11100")) return 3;
  else if(LineCompare(colors, "11101")) return 2;
  else if(LineCompare(colors, "11001")) return 1;
  else if(LineCompare(colors, "11011")) return 0;
  else if(LineCompare(colors, "10011")) return -1;
  else if(LineCompare(colors, "10111")) return -2;
  else if(LineCompare(colors, "00111")) return -3;
  else if(LineCompare(colors, "01111")) return -4;
  else return 3;
}

function constraint(value, min, max)
{
  return value > max ? max : value < min ? min : value;
}

function _convert(_pid)
{
  return constraint(MOVE_FWD+_pid, 0, 255) + " - " + constraint(MOVE_FWD-_pid, 0, 255); 
}

console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("10011> \t| " + _convert(PID(CalculateError("10011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("10111> \t| " + _convert(PID(CalculateError("10111"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("00111> \t| " + _convert(PID(CalculateError("10011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("01111> \t| " + _convert(PID(CalculateError("10011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("00111> \t| " + _convert(PID(CalculateError("10011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("10111> \t| " + _convert(PID(CalculateError("10111"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("10011> \t| " + _convert(PID(CalculateError("10011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);

console.log("\n11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11001> \t| " + _convert(PID(CalculateError("11001"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11101> \t| " + _convert(PID(CalculateError("11101"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11100> \t| " + _convert(PID(CalculateError("11100"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11110> \t| " + _convert(PID(CalculateError("11110"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11100> \t| " + _convert(PID(CalculateError("11100"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11101> \t| " + _convert(PID(CalculateError("11101"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11001> \t| " + _convert(PID(CalculateError("11001"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);


console.log("\n11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("10011> \t| " + _convert(PID(CalculateError("10011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("10111> \t| " + _convert(PID(CalculateError("10111"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("00111> \t| " + _convert(PID(CalculateError("10011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("01111> \t| " + _convert(PID(CalculateError("10011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("00111> \t| " + _convert(PID(CalculateError("10011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("10111> \t| " + _convert(PID(CalculateError("10111"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("10011> \t| " + _convert(PID(CalculateError("10011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);

console.log("\n11110> \t| " + _convert(PID(CalculateError("11110"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11100> \t| " + _convert(PID(CalculateError("11100"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
console.log("11011> \t| " + _convert(PID(CalculateError("11011"))) + "\t| P = " + P + " \t | I = " + I + "\t| D = " + D);
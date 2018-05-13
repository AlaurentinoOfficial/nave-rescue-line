var P = 0,
    I = 0,
    D = 0,
    previous_error = 0,
    Kp = 1,
    Ki = 1,
    Kd = 1;


function PID(error)
{
  P = error; // Proportional = Robot position
  I += error; // Integral = Graph Area
  D = error - previous_error; // Derivative = Error Variation (Delta ERROR)
  
  previous_error = error;
  return (Kp*P) + (Ki*I) + (Kd*D);
}

function PIDReset()
{
  I = 0;
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
  else if(LineCompare(colors, "11011")) { PIDReset(); return 0; }
  else if(LineCompare(colors, "10011")) return -1;
  else if(LineCompare(colors, "10111")) return -2;
  else if(LineCompare(colors, "00111")) return -3;
  else if(LineCompare(colors, "01111")) return -4;
  else return 3;
}

function _convert(_pid)
{
  return (200+_pid) + " - " + (200-_pid); 
}

console.log("11011> " + _convert(PID(CalculateError("11011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11001> " + _convert(PID(CalculateError("11001"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11101> " + _convert(PID(CalculateError("11101"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11100> " + _convert(PID(CalculateError("11100"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11110> " + _convert(PID(CalculateError("11110"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11100> " + _convert(PID(CalculateError("11100"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11101> " + _convert(PID(CalculateError("11101"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11001> " + _convert(PID(CalculateError("11001"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11011> " + _convert(PID(CalculateError("11011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11011> " + _convert(PID(CalculateError("11011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11011> " + _convert(PID(CalculateError("11011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11011> " + _convert(PID(CalculateError("11011"))) + "| I = " + I + " | D = " + D + " | P = " + P);

console.log("\n10011> " + _convert(PID(CalculateError("10011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("10111> " + _convert(PID(CalculateError("10111"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("10011> " + _convert(PID(CalculateError("10011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11011> " + _convert(PID(CalculateError("11011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11011> " + _convert(PID(CalculateError("11011"))) + "| I = " + I + " | D = " + D + " | P = " + P);

console.log("\n10011> " + _convert(PID(CalculateError("10011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("10111> " + _convert(PID(CalculateError("10111"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("10011> " + _convert(PID(CalculateError("10011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11011> " + _convert(PID(CalculateError("11011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
console.log("11011> " + _convert(PID(CalculateError("11011"))) + "| I = " + I + " | D = " + D + " | P = " + P);
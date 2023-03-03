#ifndef CHART_WEB_PAGE_H
#define CHART_WEB_PAGE_H

const char chartWebPage[] PROGMEM = R"=====(
<!doctype html>
<title>Mash Assistant</title>
<div>
  <div style="position: absolute; top:0; right:0; padding: 16pt;">
    <a href="/settings">
      <button>Settings</button>
    </a>
  </div>
  <div style="text-align: center; font-size: large; padding: 16pt;">
    Current temperature
  </div>
  <div id="currentTemperature" style="text-align: center; font-size: 64px;">
    N/A
  </div>
  <canvas id="myChart"></canvas>
</div>
<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<script>
  function update() {
    load("chart/data");
  }

  function load(url) {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
      if (this.readyState != 4 || this.status != 200) {
        return;
      }

      var result = this.responseText;
      var chartData = result.split(",").map(r => r.split(":")).map(a => [timestampToDate(Number(a[0])), a[1]]);
      var lastIndex = Math.max(0, chartData.length - 1);
      var currentTemperature = chartData[lastIndex][1];

      updateChart(chartData);
      updateTemperature(currentTemperature);
    }
    xhttp.open('GET', url, true);
    xhttp.send();
  }

  function timestampToDate(ts) {
    var date = new Date(ts * 1000);
    return date.toLocaleTimeString();
  }

  function updateChart(chartData) {
    chart.data.datasets[0].data = chartData;
    chart.update();
  }

  function updateTemperature(currentTemperature) {
    document.getElementById("currentTemperature").innerText = currentTemperature + " C";
  }

  const ctx = document.getElementById('myChart');
  // var result = "1677785902:50,1677785907:71,1677785912:71,1677785917:77,1677785922:43,1677785927:69,1677785932:72,1677785937:56,1677785942:49,1677785947:30,1677785952:60,1677785957:26,1677785962:59,1677785967:43,1677785972:30,1677785977:61,1677785982:41,1677785987:61,1677785992:65,1677785997:58,1677786002:51,1677786007:80,1677786012:78,1677786017:70,1677786022:45,1677786027:75,1677786032:61,1677786037:67,1677786042:50,1677786047:25,1677786052:71,1677786057:49";
  // var result = this.responseText;
  // var chartData = result.split(",").map(r => r.split(":")).map(a => [timestampToDate(Number(a[0])), a[1]]);
  var chartData = [];
  var chart = new Chart(ctx, {
    type: 'line',
    data: {
      datasets: [{
        label: "Temperature over time, C",
        data: chartData,
        borderWidth: 2,
        tension: 0.2
      }]
    },
    options: {
    }
  });

  setInterval(update, 5000);
</script>
)=====";

#endif

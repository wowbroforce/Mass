#ifndef WEB_PAGE_CONTENT_H
#define WEB_PAGE_CONTENT_H

const char webpage[] PROGMEM = R"=====(
<div>
  <canvas id="myChart"></canvas>
</div>

<script src="https://cdn.jsdelivr.net/npm/chart.js"></script>

<script>
  const ctx = document.getElementById('myChart');
  
  new Chart(ctx, {
    type: 'line',
    data: {
      labels: Utils.months({count: 7}),
      datasets: [{
        label: 'My First Dataset',
        data: [65, 59, 80, 81, 56, 55, 40],
        fill: false,
        borderColor: 'rgb(75, 192, 192)',
        tension: 0.1
      }]
    },
    options: {
      title: {
        display: true,
        text: 'World population per region (in millions)'
      }
    }
  });
</script>
)=====";

#endif

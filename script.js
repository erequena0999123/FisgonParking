document.addEventListener('DOMContentLoaded', function () {
    // Assume you have a WebSocket connection with your ESP8266
    const socket = new WebSocket('ws://your-esp8266-ip-address:your-port');

    socket.addEventListener('message', function (event) {
        const distanceValue = document.getElementById('distance-value');
        const distanceData = JSON.parse(event.data);

        // Assuming the distance is sent in centimeters
        distanceValue.textContent = distanceData.distance + ' Cm';
    });
});

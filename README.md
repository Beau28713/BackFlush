
  <h1>💧 Automated Back Flush Filtration System</h1>
  <p>This system automates the back-flush cycle of a sediment filter using Arduino-based controls, designed for water efficiency and reduced maintenance in home and small-scale environments.</p>

  <hr>

  <div class="section">
    <h2>🔧 System Overview</h2>
    <ul>
      <li><strong>Controller:</strong> Arduino Uno WiFi Rev 2</li>
      <li><strong>Sensors:</strong> Pressure sensor, digital flow meter</li>
      <li><strong>Actuators:</strong> 12V solenoid valves</li>
      <li><strong>Display:</strong> 20x4 I2C LCD</li>
      <li><strong>Input:</strong> Manual control buttons</li>
      <li><strong>Power:</strong> 12V DC with onboard regulation</li>
    </ul>
  </div>

  <div class="section">
    <h2>⚙️ Key Features</h2>
    <ul>
      <li>Time- or pressure-triggered flush cycles</li>
      <li>Real-time LCD monitoring of system state</li>
      <li>Manual override and configurable intervals</li>
      <li>3D-printed enclosures for hardware protection</li>
    </ul>
  </div>

  <div class="section">
    <h2>🧠 Control Logic</h2>
    <pre><code>if (millis() - lastFlushTime > flushInterval || pressureDropDetected()) {
    initiateBackFlush();
}</code></pre>
    <p>Flushes automatically on a timer or when filter clogging is detected.</p>
  </div>

  <div class="section">
    <h2>🛠️ Design & Hardware</h2>
    <ul>
      <li>Enclosure designs created in Fusion 360</li>
      <li>LCD displays pressure, valve status, and countdowns</li>
      <li>Custom wiring and logic layout on perfboard</li>
    </ul>
  </div>

  <div class="section">
    <h2>🚀 Future Upgrades</h2>
    <ul>
      <li>MQTT integration for wireless updates</li>
      <li>Modbus RTU for Ignition SCADA integration</li>
      <li>Pressure trend logging with SD card or WiFi</li>
    </ul>
  </div>

  <div class="section">
    <h2>📸 Media (Coming Soon)</h2>
    <p>Photos, LCD screenshots, and enclosure views will be added shortly.</p>
  </div>

  <div class="section">
    <h2>🔗 Links</h2>
    <ul>
      <li><a href="https://github.com/Beau28713/Beau28713.github.io/tree/main/back%20flush">Source Code on GitHub</a></li>
      <li><a href="https://beau28713.github.io">Main Site</a></li>
    </ul>
  </div>

</body>
</html>

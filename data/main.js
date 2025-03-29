
let token = "";
let role = "";
let ws;

function login() {
  const username = document.getElementById("username").value;
  const password = document.getElementById("password").value;

  fetch("/api/login", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ username, password })
  })
    .then(res => res.json())
    .then(data => {
      token = data.token;
      role = data.role;
      document.getElementById("login").style.display = "none";
      document.getElementById("control").style.display = "block";
      if (role === "admin") {
        document.getElementById("adminPanel").style.display = "block";
      }
      connectWebSocket();
      fetchLogs();
    });
}

function logout() {
  token = "";
  role = "";
  ws?.close();
  document.getElementById("login").style.display = "block";
  document.getElementById("control").style.display = "none";
  document.getElementById("adminPanel").style.display = "none";
}

function startMotor() {
  const timer = parseInt(document.getElementById("timer").value);
  if (timer < 1 || timer > 30) return alert("1-30 min only");

  fetch("/api/motor/start", {
    method: "POST",
    headers: {
      "Authorization": `Bearer ${token}`,
      "Content-Type": "application/json"
    },
    body: JSON.stringify({ timer })
  });
}

function stopMotor() {
  fetch("/api/motor/stop", {
    method: "POST",
    headers: { "Authorization": `Bearer ${token}` }
  });
}

function fetchLogs() {
  fetch("/api/logs", {
    headers: { "Authorization": `Bearer ${token}` }
  })
    .then(res => res.json())
    .then(data => {
      window.motorLogs = data.motorLogs;
      window.dailyLogs = data.dailyLogs;
      renderLogs();
    });
}

function renderLogs() {
  const filter = document.getElementById("dayFilter").value;
  const motorLogsDiv = document.getElementById("motorLogs");
  const dailyLogsDiv = document.getElementById("dailyLogs");

  motorLogsDiv.innerHTML = "";
  window.motorLogs?.filter(log => filter === "All" || log.day === filter)
    .forEach(log => {
      motorLogsDiv.innerHTML += `<p>${log.timestamp} - ${log.action} by ${log.user} (${log.timer_value} min)</p>`;
    });

  dailyLogsDiv.innerHTML = "";
  window.dailyLogs?.filter(log => filter === "All" || log.day === filter)
    .forEach(log => {
      dailyLogsDiv.innerHTML += `<p>${log.date} (${log.day}): ${log.start_count} starts</p>`;
    });
}

function switchTab(tab) {
  document.getElementById("motorLogsTab").classList.remove("active");
  document.getElementById("dailyLogsTab").classList.remove("active");
  document.getElementById(`${tab}LogsTab`).classList.add("active");
}

function connectWebSocket() {
  ws = new WebSocket("ws://" + window.location.hostname + ":81");

  ws.onmessage = function(event) {
    const msg = JSON.parse(event.data);
    if (msg.type === "MOTOR_STATUS") {
      document.getElementById("status").textContent = msg.isRunning ? `Running (${msg.timer} min)` : "Stopped";
    }
  };
}

function changeUserRole() {
  const username = document.getElementById("roleUser").value;
  const newRole = document.getElementById("newRole").value;

  fetch("/api/users/role", {
    method: "POST",
    headers: {
      "Authorization": `Bearer ${token}`,
      "Content-Type": "application/json"
    },
    body: JSON.stringify({ username, role: newRole })
  }).then(() => alert("Role updated!"));
}

function changePassword() {
  const username = document.getElementById("passUser").value;
  const password = document.getElementById("newPassword").value;

  fetch("/api/users/password", {
    method: "POST",
    headers: {
      "Authorization": `Bearer ${token}`,
      "Content-Type": "application/json"
    },
    body: JSON.stringify({ username, password })
  }).then(() => alert("Password changed!"));
}

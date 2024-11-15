<<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Gestión de Tareas con Prioridades y Deshacer</title>
    <style>
        body {
            font-family: "Helvetica", "Arial", sans-serif;
            margin: 0;
            padding: 0;
            background-color: #f4f4f9;
        }
        header {
            background-color: #963a3a;
            color: rgb(255, 255, 255);
            padding: 10px 0;
            text-align: center;
        }
        .container {
            padding: 80px;
            color: rgb(0, 0, 0);
            background-color: #e6a3cf;
        }
        .task-list {
            margin: 20px 0;
        }
        .task {
            padding: 10px;
            margin: 10px 0;
            border-radius: 5px;
            background-color: #f0f0f0;
            display: flex;
            justify-content: space-between;
            align-items: center;
        }
        .priority {
            padding: 5px;
            border-radius: 3px;
        }
        .low {
            background-color: #bb5db3;
        }
        .medium {
            background-color: #f38b15;
        }
        .high {
            background-color: #acf854;
        }
        .task-actions button {
            padding: 5px 10px;
            margin-left: 10px;
            background-color: #4CAF50;
            color: rgb(223, 197, 197);
            border: none;
            cursor: pointer;
            border-radius: 5px;
        }
        .task-actions button:hover {
            background-color: #45a049;
        }
        .task-actions input[type="checkbox"] {
            margin-left: 10px;
        }
        button {
            padding: 10px 15px;
            background-color: #4CAF50;
            color: white;
            border: none;
            cursor: pointer;
            border-radius: 5px;
        }
        button:hover {
            background-color: #45a049;
        }
    </style>
</head>
<body>
    <header>
        <h1>Gestión de Tareas</h1>
    </header>
    <div class="container">
        <h2>Agregar Nueva Tarea</h2>
        <input type="text" id="taskName" placeholder="Nombre de la tarea" required>
        <select id="taskPriority">
            <option value="Baja">Baja</option>
            <option value="Medio">Media</option>
            <option value="Alta">Alta</option>
        </select>
        <button onclick="addTask()">Agregar Tarea</button>

        <h2>Listas de Tareas</h2>
        <div id="waitingTasks" class="task-list">
            <h3>Tareas en Espera</h3>
        </div>
        <div id="undoTasks" class="task-list">
            <h3>Tareas Deshechas</h3>
        </div>
    </div>

    <script>
        
        let waitingTasks = [];
        let undoneTasks = [];

       
        function addTask() {
            const taskName = document.getElementById('taskName').value;
            const taskPriority = document.getElementById('taskPriority').value;

            if (taskName.trim() === '') {
                alert('Por favor ingresa el nombre de la tarea');
                return;
            }

            const task = {
                name: taskName,
                priority: taskPriority,
                isUndone: false // Marca si la tarea es deshecha y puede revertirse
            };

            waitingTasks.push(task);
            renderTasks();
            document.getElementById('taskName').value = ''; // Limpiar el
        }

        
        function markAsUndone(taskName) {
            const task = waitingTasks.find(t => t.name === taskName);
            if (task) {
                task.isUndone = true;
                undoneTasks.push(task);
                
                waitingTasks = waitingTasks.filter(t => t.name !== taskName);
                renderTasks();
            }
        }

        
        function undoTask(taskName) {
            const task = undoneTasks.find(t => t.name === taskName);
            if (task) {
                task.isUndone = false;
                waitingTasks.push(task);
              
                undoneTasks = undoneTasks.filter(t => t.name !== taskName);
                renderTasks();
            }
        }

       
        function renderTasks() {
            
            document.getElementById('waitingTasks').innerHTML = '<h3>Tareas en Espera</h3>' + renderTaskList(waitingTasks, 'waiting');

            
            document.getElementById('undoTasks').innerHTML = '<h3>Tareas Deshechas</h3>' + renderTaskList(undoneTasks, 'undone');
        }

       
        function renderTaskList(taskList, type) {
            if (taskList.length === 0) {
                return '<p>No hay tareas</p>';
            }

            return taskList.map(task => `
                <div class="task ${task.priority}">
                    <div>
                        <strong>${task.name}</strong> 
                        <span class="priority">${task.priority.charAt(0).toUpperCase() + task.priority.slice(1)}</span>
                    </div>
                    <div class="task-actions">
                        ${type === 'waiting' ? 
                            `<input type="checkbox" onclick="markAsUndone('${task.name}')"> Marcar como deshecha` : 
                            `<button onclick="undoTask('${task.name}')">Revertir</button>`
                        }
                    </div>
                </div>
            `).join('');
        }

        
        renderTasks();
    </script>
</body>
</html>




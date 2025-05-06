This program creates a **daemon process** — a background process detached from a terminal — commonly used for logging, system monitoring, and background services.

---

## 🔧 Breakdown of the Code:

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>
```

### 🔹 Headers:

* `stdio.h` and `stdlib.h`: standard C I/O and exit functions
* `sys/stat.h` and `sys/types.h`: for file modes and types
* `syslog.h`: for writing logs to the system logger
* `unistd.h`: for process-related system calls like `fork()`, `setsid()`, etc.
* `fcntl.h`: for file descriptor operations (`open()`)

---

## 🧩 `create_daemon()` Function — Core Logic

### 1. 🔄 `fork()` — Create a Child

```c
pid_t pid = fork();
```

* `fork()` creates a new process.
* If `pid > 0`, we’re in the **parent** → we `exit()`.
* This ensures the parent dies, and the child is **not a process group leader** (a requirement for `setsid()` to work).

```c
if (pid > 0) {
    exit(EXIT_SUCCESS); // Parent exits
}
```

---

### 2. 🧭 `setsid()` — Create New Session

```c
setsid();
```

* The child becomes:

  * Session leader
  * Process group leader
  * Has **no controlling terminal**
* This is the key step that **detaches the process from the terminal**.

---

### 3. 🧼 `umask(0)` — Clear File Mode Creation Mask

```c
umask(0);
```

* Ensures the daemon can create files with **any permission** needed.
* Prevents it from inheriting restrictive file permissions.

---

### 4. 📂 `chdir("/")` — Change Working Directory

```c
chdir("/");
```

* The daemon switches to root (`/`) so it doesn't keep any directory in use (e.g., a mounted filesystem that shouldn't be held up).

---

### 5. 🔇 Redirect File Descriptors

```c
open("/dev/null", O_RDONLY); // dummy stdin
open("/dev/null", O_WRONLY); // dummy stdout
open("/dev/null", O_RDWR);   // dummy stderr
```

* `/dev/null` discards all input/output.
* Opening this ensures the daemon won’t accidentally read from/write to the terminal.

```c
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
```

* Close the actual standard file descriptors so they don’t interfere.

---

## 🧠 `main()` Function — Daemon Logic

```c
create_daemon();  // Initialize the daemon process
```

### 6. 🧾 `openlog()` — Start Logging

```c
openlog("daemon_ex", LOG_PID, LOG_DAEMON);
```

* `daemon_ex`: tag shown in log messages
* `LOG_PID`: logs the PID
* `LOG_DAEMON`: identifies the facility (daemon-related logs)

---

### 7. 🔁 Daemon Loop

```c
while (1) {
    syslog(LOG_NOTICE, "Daemon is running...\n");
    sleep(30);
}
```

* Writes a log every 30 seconds.
* Typically replaced with actual daemon work (e.g., monitoring, triggering actions, etc.)

---

### 8. 🛑 `closelog()` — Cleanup (unreachable in this code unless loop breaks)

```c
closelog();
```

---

## 🧪 Run Notes:

To run and check logs:

1. Compile the program:

   ```bash
   gcc -o daemon_ex p2_daemon.c
   ./daemon_ex
   ```

2. Check logs (location varies):

   ```bash
   tail -f /var/log/syslog       # Ubuntu/Debian
   tail -f /var/log/messages     # RHEL/CentOS
   ```

---

## 📌 Summary of Daemon Creation Steps:

| Step | Action                     | Purpose                                     |
| ---- | -------------------------- | ------------------------------------------- |
| 1    | `fork()` and kill parent   | Ensure the process is not session leader    |
| 2    | `setsid()`                 | Become session leader and detach terminal   |
| 3    | `umask(0)`                 | Clear file permission mask                  |
| 4    | `chdir("/")`               | Avoid directory locks                       |
| 5    | Close std file descriptors | Detach from terminal                        |
| 6    | `openlog()` and loop       | Run actual daemon logic with system logging |

Would you like to enhance this with PID file creation or signal handling?

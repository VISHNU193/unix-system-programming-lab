Sure! In **C programming**, a **storage class** defines:

- **Scope**: Where the variable can be accessed.
- **Lifetime**: How long the variable exists in memory.
- **Default initial value**.
- **Linkage**: Whether the variable is known in other files.

There are **four storage classes** in C:

---

## ✅ 1. `auto` (Automatic Storage Class)
- **Scope**: Local to the block (function, loop, etc.)
- **Lifetime**: Exists during the execution of the block.
- **Default value**: **Garbage** (undefined).
- **Storage**: Stored in **stack**.

```c
#include <stdio.h>
void func() {
    auto int x = 10;  // Same as: int x = 10;
    printf("%d\n", x);
}
```

> ⚠️ `auto` is rarely used explicitly since local variables are `auto` by default.

---

## ✅ 2. `register` (Register Storage Class)
- **Scope**: Local to the block.
- **Lifetime**: During the block execution.
- **Default value**: Garbage.
- **Storage**: Stored in **CPU register** (if available).
- **Access**: **Address cannot be obtained using `&`**.

```c
#include <stdio.h>
void func() {
    register int i = 5;
    printf("%d\n", i);
    // printf("%p", &i);  // ❌ Error: address of register variable
}
```

> ✅ Use for **loop counters** or variables that need fast access.

---

## ✅ 3. `static` (Static Storage Class)

### → For **local variables**:
- **Scope**: Local to the block.
- **Lifetime**: Exists for the **entire program** (not recreated on each function call).
- **Default value**: 0.
- **Storage**: Stored in **data segment**.

```c
#include <stdio.h>
void func() {
    static int count = 0;
    count++;
    printf("%d\n", count);
}
int main() {
    func();  // 1
    func();  // 2
    func();  // 3
}
```

> 🧠 The value of `count` **persists between function calls**.

### → For **global variables or functions**:
- **Scope**: File-level (internal linkage).
- **Lifetime**: Entire program.
- **Used to restrict visibility** of a function/variable to the same file.

```c
static int global_var = 10;  // Can't be accessed from other files
```

---

## ✅ 4. `extern` (External Storage Class)
- **Used to declare a variable/function defined in another file.**
- **Scope**: Global.
- **Lifetime**: Entire program.
- **Default value**: 0 (if global).
- **Storage**: Stored in data segment.

### Example with two files:

#### File: `file1.c`
```c
int x = 100;  // Definition
```

#### File: `file2.c`
```c
#include <stdio.h>
extern int x;  // Declaration
int main() {
    printf("%d", x);  // Uses x from file1
    return 0;
}
```

> ✅ Helps in sharing variables/functions **across multiple files**.

---

## 🔄 Summary Table:

| Storage Class | Scope      | Lifetime         | Default Value | Linkage        |
|---------------|------------|------------------|----------------|----------------|
| `auto`        | Local      | Block             | Garbage        | No linkage     |
| `register`    | Local      | Block             | Garbage        | No linkage     |
| `static`      | Local/Global | Program          | 0              | Internal (file)|
| `extern`      | Global     | Program           | 0              | External       |

---

Let me know if you want to see examples with multiple files or explore **memory layout** of these classes!
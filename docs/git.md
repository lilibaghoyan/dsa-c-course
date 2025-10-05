# Git Guide

This guide explains the **basic concepts** of Git and gives you the **commands you need** to work on assignments, push your changes, and open Pull Requests (PRs).

---

## 1. Key Concepts

### Repository (Repo)

* A **repo** is your project folder managed by Git.
* It exists in two places:

  * **Local** → on your computer.
  * **Remote** → on GitHub (shared).

```
Local (your laptop)   <----->   Remote (GitHub)
```

---

### Branch

* A **branch** is like a **separate timeline of code**.
* Default branch is usually called `main`.
* You make a new branch for each feature or assignment.

```
main:      A ---> B ---> C
                 \
my-branch:        D ---> E
```

---

### Stage

* The **staging area** is like a **shopping cart** for changes.
* Edit → `git add file.c` → change is staged.
* `git commit` → everything staged is saved.

```
Working Directory ---> Staging Area ---> Commit (history)
```

---

### Commit

* A **commit** is like a **save point** (checkpoint).
* Includes your changes + message.
* Commits form the project history:

```
A ---> B ---> C ---> D
```

---

### Local vs Remote

* **Local** = on your computer.
* **Remote** = on GitHub.
* You push commits **up**, you pull commits **down**.

```
Local Repo
   |  git push
   v
Remote Repo (GitHub)
   ^  git pull
   |
```

---

## 2. Setup

Configure Git once:

```bash
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
```

Check config:

```bash
git config --list
```

---

## 3. Basic Workflow

### Clone a Repo

```bash
git clone https://github.com/username/repo-name.git
cd repo-name
```

### Create a Branch

```bash
git checkout -b my-assignment
```

### Make Changes → Stage → Commit

```bash
git status                 # see what changed
git add file1.c file2.c    # stage files
git commit -m "Implemented binary search"
```

### Push Branch to GitHub

```bash
git push origin my-assignment
```

---

## 4. Keeping Up to Date

### Pull Latest Changes into Main

```bash
git checkout main
git pull origin main
```

### Merge Main into Your Branch

```bash
git checkout my-assignment
git merge main
```

---

## 5. Opening a Pull Request

1. Push your branch:

   ```bash
   git push origin my-assignment
   ```
2. Go to GitHub → select your branch.
3. Click **“Open Pull Request”**.
4. Write a short description of what you did.
5. Submit PR.

---

## 6. Undoing Mistakes

* **Undo last commit (keep changes):**

  ```bash
  git reset --soft HEAD~1
  ```
* **Undo last commit (discard changes):**

  ```bash
  git reset --hard HEAD~1
  ```
* **Unstage a file:**

  ```bash
  git reset file.c
  ```
* **Discard file edits:**

  ```bash
  git checkout -- file.c
  ```

---

## 7. Stashing (Save Work Temporarily)

If you need to switch branches but aren’t ready to commit:

```bash
git stash
git checkout main
```

Bring changes back:

```bash
git stash pop
```

---

## 8. Rebasing (Optional)

Rebase puts your commits on top of the latest main branch:

```bash
git checkout my-assignment
git fetch origin
git rebase origin/main
```

Diagram:

Before rebase:

```
main:       A ---> B ---> C
                  \
my-branch:         D ---> E
```

After rebase:

```
main:       A ---> B ---> C
                           \
my-branch:                  D’ ---> E’
```

---

## 9. Cheat Sheet

* `git clone URL` → copy repo
* `git checkout -b branch` → new branch
* `git status` → check changes
* `git add .` → stage everything
* `git commit -m "msg"` → save checkpoint
* `git push origin branch` → upload branch
* `git pull origin main` → update main
* `git merge main` → merge main into branch
* `git reset --hard` → undo changes
* `git stash` / `git stash pop` → save/restore work

---

## 10. Typical Assignment Flow

```
Clone repo
    |
    v
Create branch ---> Work on code ---> git add + commit ---> Push branch
                                               |
                                               v
                                Keep branch updated (pull/merge/rebase)
                                               |
                                               v
                                       Open Pull Request (PR)
```

---

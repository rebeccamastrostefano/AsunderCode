# AsunderCode

🛠️ C++ Source Code for **Asunder** – an Unreal Engine game currently in development.

This repository contains only the **gameplay C++ code** for Asunder. It excludes heavy project files (assets, editor data, binaries) to keep the repository lightweight and focused on the programming side of development.

---

## 🧠 About the Project

**Asunder** (working title) is a **2.5D narrative puzzle-platformer made in Unreal Engine**, where two characters navigate a side-scrolling world divided by an **interactive split line**. I built **all core gameplay systems in C++** and created **custom shaders and post-process effects** to visually and interactively define the "split" mechanic. One key challenge was achieving a **performant, frame-accurate screen-space division**. without relying on CPU-driven logic — solved via a fully GPU-based shader pipeline.

🔹 Written entirely in C++  
🔹 Developed **core gameplay logic in C++**, including: **Spline-based dynamic divider system** that updates in real-time based on player positions. **Physics-aware split collider** that aligns with the visual divider;  
🔹 Built **post-process shaders in HLSL** via Unreal’s Custom Node to compute **screen-space masks** from world-space player data;  
🔹 Designed and implemented **render target setup to simulate player-specific visibility** (e.g., different decorations per character);  
🔹Designed the **gameplay and narration**.  




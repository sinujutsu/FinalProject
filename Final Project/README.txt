Basics
-Space to move in
-Shooting *Ian
-Controls *Ian
-An (1) enemy *Jake
-Collision Response *Nick
Advanced
-Phong Shading *Ian
-Multiple Cameras (One overhead, one static)
-Texture Mapped Object(background/playing field) *Jake
-Texture Mapped Mesh Object?
-HUD (Score/lives)
Extra
-Music
-Dem Trippy Visuals
-Friction across all moving objects

Player mesh: to tie it to the PlayerObject class, take the mesh and "do it" in a display list, and put a display list field in the class.
This way, it should be initialized in the display list, and thus easily editable from the class.
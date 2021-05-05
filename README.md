# TheMageRunner

-Category:
+ SDL2
+ 2d
+ Pixel art
+ Mario-like
+ Contra-like
+ Puzzle

-Script 1st : (unused)
+ A mage are escaping from a moving wall (or spike) after taking the temple's treasure.
+ On the way out, there are multiple monsters, both elemental and non-elemental, the mage have to use the correct spell type to clear the way.
+ There are also mystical artifact on the way out, the mage can take it and enhance himself, maybe attack, speed, lives, ...
+ When the mage reach the door to the way out, a giant dragon (or stone man) appears to be the treasure's guardian, arrives, the mage has to fight his way through.
+ The wall(spike) will move slower, the mage dont have much time (and space) to fight the boss, so he has to manage quickly. (maybe 3 minutes?)
+ The boss will be, incredibly strong, when the mage's live is too little, or the wall has reached too close, he will receive a power, power which is so strong for him can manage.
+ The power, will be called the power of friendship, cause the reason of him coming all his way here is to save his sister, (flash back : numerous of his friend has also sacrifice themselves just for him to be able to achieve the treasure), so he cant lose.
+ After that, the mage will be, 10x stronger, he use all the remaining power left to make a single blow, the dragon die after that, the mage fainted.
+ While he was fainting, he heard the call, of his sister, after that, he gently open up his eye, move slowly toward the temple's door.
+ To be continue...

-Script 2nd : (used)
+ In order to search for the memory a mage has lost for centuries, he ask an old sage, he pointed the mage to come to the cave in the Forgotten Continent.
+ He has found the entrance, and eager to enter.
+ Without memory, he cant cast any high-level skill, even low-level skill he can only cast, is fire-ball.
+ The memory can be restore, if he have the Crystal Of Remembrance, a magical crystal that can restore a person's memory, which is placed at the end of the cave, guarded by a giant boss (giant stone-man or giant dragon).
+ (Changing from script 1st) : power at the end, changing to power of will ("remember who u are.."), not power of friendship.

-30/4/2021: Updating utils
+ Each map will be divided into sub-levels, each sub-level will be puzzle-like, have to meet some condition to pass (like get the proper skill to pass through hordes of enemies, finding the key to unlock the hidden cave, ...)
+ Prolong the current map (map03.txt), remember make some cliff
+ Making some mechanic like animation item (using tile will be easy). (Done)
+ Input action mechanic improve. (DONE)
+ Some puzzle-like mechanic to pass sub-level like elevator platform, portal to teleport, utilize the current skill to do smt, ...
+ Generate platforms frequently.
+ Improve collision detection (now still ver 1.0 - 90o collision detect)
+ Need to make enemies look like flying.
+ Stagger effect need to make. (DONE)
+ KO effect need to make. (DONE)
+ Skill animation need to make.
+ Speed threat bullet when center entity need to fix. (Done)

-1/5/2021: Updating utils
+ Making backstory for 2nd script, making typing animation (interior monologue - độc thoại nội tâm).
+ Making multiple render-in-game animation (first just create 3 scenes : 1 before entering the cave, 1 before fighting the boss, 1 after finishing the boss 1st time.)
+ Making background fake-moving (just 2 bottom layer)
+ Making save game.
+ Making bullet threat collision with tile map.
+ Making more types of enemy (water wisp, poison snake, ...)
+ Making menu + submenus. (main menu, continue, pause menu)
+ Making item (drop after killing enemies or inside chest) like potions.
+ Making buff and debuff status. Debuff causes by environment (ex. room full of toxic gas) or causes by enemy (ex. fireball makes burn-debuff, axit spit makes poison-debuff).
Buff causes by drinking potions.
+ Making hp and mp status (mp can self-replenish with an amount of time)
+ Making player's monologue while playing the main story.
+ Making tutorials
+ Making more skill like self-heal (has cool down), toggle magic barrier (consume mp when cast, consume more when it get hit), ...
+ Synchroize object texture and convo (HARD)

-2/5/2021: Updating script 2nd
+ After press NEW GAME, runs the 1st animation about the mage's interior monologue when he losts his memory. (DONE) After that, the screen becomes pitch black, and suddenly a pixie fly from the right screen border in zic-zac hyperbolic direction (CONSIDER THIS COULD BE HARD), stops in front of the screen, introduce herself and ask if the player wants to run through the tutorial or not. If YES, load the tile map tutorial. If NO, entering the main story.

+ In the tutorial, movement, toggle-skill, buff, debuff, puzzle objective, hp, mp, key-item ... will be explained. While explaining, the texture has to made blur (as blur as possible), the explaining will be made by text animation, to end explaining, press any key. Do not explaing everything, let the player explore him/her self. After finish the last objective in the tutorial, entering the main story.

+ Main story will go on, add some render-in-game animation insides. After he solves all the puzzle-like, he reaches the treasure's of the Continent, the Crystal of Remembreance.

+ Making fight boss stage (The boss is a giant dragon). Stage 1, the dragon is on ground, the mage have to evade + shoot to defeat it. After its hp reaches 0, the dragon reborns, entering its true form - flying. Enter stage 2, the dragon flys above the maximum height of a mage could jump, the way out is also block (block from the stage 1), it breathes multiple fireball (stage 1 is one fire ball at a time, fricking easy to evade) , the mage try his best to evade but sooner or later, he will eventually KO. But this is part of the story. 
(Run some interior monologue here to express his feelings). 

+ After the mage KO (not die yet), the Crystal of Remembreance activates its magical effect. Turns out it can also heal the damage on the mage, also let him remember everything before the adventure.
(PLOT TWIST : The reason why the mage lost his memory is because of his numerous tries of creating of flying spell, a spell that manipulate the wind element to lift the mage up and fly in any direction. In this world, man haven't be able to fly, monster like dragon or wisp could though, so he - one of the best mages in the Center Continent, study the wind element day by day, experiments what he found continuously. This is very dangerous, one mistake can cost his life. One day, he has reached the peak of his research, attempting the last experiment, and it works, it finally works, but an accident happens on that test flight, he crashes, luckily it didn't cost his life, but his memory is gone. No matter how hard he tried, he just can't remember anything before the accident, the only thing remains is his name, Visage (sound like VH + sage/mage).

+ Back to the present, the dragon's shocking, ask who the mage is. The mage answer, "I AM VISAGE, THE ONE AND ONLY MAGE CAN REACH THE SKY". The dragon's infuriate, casting multiple fireball towards the mage, the mage casts his flying skill, evade every last one of fireballs (MINI GAME HERE : QUICK TIME EVENT, press the correct key to evade, if you press wrong, you will get hit, if you get hit too much, you will lose and have yo try again).

+ The mage flys round the back of the dragon, hit it with multiple spell (lighting, fireball, ice shard, wind cut). The dragon then die, leaving some lasts word "YOU WIN, HUMAN". The mage then collapses "I... FINALLY.. WON". The screen fading here, the pixie then reappears, told that the mage's destiny is just begin, there will be a long journey ahead him, blesses him and the screen fades again. Run the credits.

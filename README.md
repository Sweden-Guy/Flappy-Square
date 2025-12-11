## Flappy square is a Flappybird inspired game for an Arduino UNO R3. 
Flappy Square is an arcade style game in which the player controls the square which moves to the right. You are tasked with navigating the square through pairs of pipes that have equally sized gaps placed at random heights. The square automatically descends and only ascends when the player presses the button. Each successful pass through a pair of pipes awards the player one point. Colliding with a pipe or the ground ends the gameplay. 

I have added many comments to the code so that if you want you can fix the code to suit yourself better. 

If you want, you are welcome to comment on your high score so that others can try to achieve a better high score. If many people comment on their scores, maybe I will create a leaderboard. 

All the pictures and files you need can be found further down. I hope everyone likes flappy square, and if you do please show me some respect by hitting the thumbs up so that more people can find this project. =) 

## How to Set Up (Be careful to connect everything correctly so that you don't accidentally break anything!)

### Remember it can say both SCK and SLC but they are the same.

## Arduino UNO R3 Wiring

### OLED to Arduino UNO R3
| OLED Pin | Arduino UNO Pin |
|----------|-----------------|
| GND      | GND             |
| VCC      | 3.3V            |
| SCL      | A5              |
| SDA      | A4              |

### Button to Arduino UNO R3
| Button Pin | Arduino UNO Pin |
|------------|-----------------|
| One side   | Digital 2       |
| Other side | GND             |

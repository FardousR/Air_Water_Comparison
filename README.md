|------------------|---------------------------------------------------------|-------------------|---------------------------------|
| Flag             | Description                                             | Type              | Example Usage                   |
|------------------|---------------------------------------------------------|-------------------|---------------------------------|
| `-d <value>`     | Set the grid-phantom distance (in mm)                   | Floating-point    | `-d 30.0`                       |
| `-sadx <value>`  | Set the source-to-axis distance in X (SADx) (in mm)     | Floating-point    | `-sadx 50.0`                    |
| `-sady <value>`  | Set the source-to-axis distance in Y (SADy) (in mm)     | Floating-point    | `-sady 45.0`                    |
| `-csx <value>`   | Set the collimator X-shift (in mm)                      | Floating-point    | `-csx 20.0`                     |
| `-csy <value>`   | Set the collimator Y-shift (in mm)                      | Floating-point    | `-csy 10.0`                     |
| `-agx <value>`   | Set the collimator X-angle (in radians)                 | Floating-point    | `-agx 0.02`                     |
| `-agy <value>`   | Set the collimator Y-angle (in radians)                 | Floating-point    | `-agy 0.03`                     |
| `-agz <value>`   | Set the collimator Z-angle (in radians)                 | Floating-point    | `-agz 0.01`                     |
| `-c <value>`     | Set the center-to-center distance (in mm)               | Floating-point    | `-c 2.0`                        |
| `-l <value>`     | Set the grid thickness (in mm)                          | Floating-point    | `-l 30.0`                       |
| `-t <value>`     | Set the grid throughput (as a percentage)               | Floating-point    | `-t 50.0`                       |
| `-m <value>`     | Set the grid material                                   | String            | `-m tungsten`                   |
| `-a <value>`     | Set the grid angle (in degrees)                         | Floating-point    | `-a 0.0`                        |
| `-C <value>`     | Set the number of threads to use                        | Integer           | `-C 4`                          |
| `-O <value>`     | Set the output file name                                | String            | `-O output.root`                |
| `-S <value>`     | Set the SOBP (Spread-Out Bragg Peak) file               | File path         | `-S sobp_file.dat`              |
| `-n <value>`     | Set the number of particles to simulate                 | Integer           | `-n 100000`                     |
| `-mipx <value>`  | Set the minimum PTV boundary in the X direction (in mm) | Floating-point    | `-mipx 10.0`                    |
| `-mipy <value>`  | Set the minimum PTV boundary in the Y direction (in mm) | Floating-point    | `-mipy 15.0`                    |
| `-mipz <value>`  | Set the minimum PTV boundary in the Z direction (in mm) | Floating-point    | `-mipz 20.0`                    |
| `-mapx <value>`  | Set the maximum PTV boundary in the X direction (in mm) | Floating-point    | `-mapx 50.0`                    |
| `-mapy <value>`  | Set the maximum PTV boundary in the Y direction (in mm) | Floating-point    | `-mapy 55.0`                    |
| `-mapz <value>`  | Set the maximum PTV boundary in the Z direction (in mm) | Floating-point    | `-mapz 60.0`                    |
| `-binx <value>`  | Set the bin width in the X direction (in mm)            | Floating-point    | `-binx 5.0`                     |
| `-biny <value>`  | Set the bin width in the Y direction (in mm)            | Floating-point    | `-biny 5.0`                     |
| `-binz <value>`  | Set the bin width in the Z direction (in mm)            | Floating-point    | `-binz 5.0`                     |
| `-g`             | Enable the graphical user interface (GUI)               | No argument       | `-g`                            |
| `-b`             | Enable batch mode                                       | No argument       | `-b`                            |
| `-G`             | Enable grid functionality                               | No argument       | `-G`                            |
| `-h`             | Show the help message                                   | No argument       | `-h`                            |
|------------------|---------------------------------------------------------|-------------------|---------------------------------|

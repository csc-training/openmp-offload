## Optimizing heat equation solver

Try to improve the performance of the heat equation solver by optimizing data movements.
During the time evolution iteration, the data can be mostly kept within the device.

Add apprioriate OpenMP constructs to the main routine, and modify the constructs in
`evolve()` accordingly. Are you able to improve the performance?

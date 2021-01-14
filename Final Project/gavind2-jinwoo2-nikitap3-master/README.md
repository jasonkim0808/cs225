# Gavin, Jason, and Nikita present:
# Safe Airline Finder to Escape COVID - SAFECOVID

https://img.shields.io/github/issues/jasonkim0808/CS225

We use the OpenFlights dataset (stored in the data folder as edges.txt) to search for the safest and
efficient path to travel from one airport to another. The safest route means that the
chance of getting the COVID is the lowest. This is be determined by
analyzing the number of paths at each location, since a greater number of paths
implies a busier airport, therefore more people and a greater chance of catching COVID.
The most efficient route means that the number of airports on the path will be lowest.
Also, we allow for landmarks to travel through specific locations. If the person
would like to visit a stop along the way, then we ensure that
our path from start to end includes this intermediate landmark.

To run SAFECOVID, please run "make" followed by "./safecovid" in the terminal.
After this, please follow all prompts in the terminal.

The inital process of getting the data and creating the initial graph may take
up to two minutes to complete. If more than two minutes have passed, press 'Ctrl+C'.
This will either exit so you may restart or move to the next step.

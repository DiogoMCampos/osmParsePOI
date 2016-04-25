## Why

One university project ([CAL-Project-1](https://github.com/Caramelo18/CAL-Project-1)) required us to deal with maps and 
we decided to use the parser provided by the professor to read information from OpenStreetMap. 
Unfortunately, that program converted only the nodes and edges (representing intersections and roads) and we wanted to use information from some **points of interest**.

## What

In order to accomplish that, we developed a tool that, given a ".osm" file, returns a ".txt" file with information about points of interest.
We decided the only points we would be using would be:
* ATMs
* Hospitals
* Pharmacies
* Petrol Stations
* Restaurants

It is easy to modify the program to extract information about other amenities, feel free to do it!

## Usage

Export a ".osm" file from OpenStreetMap, run osmParsePOI and input the name of the file. It will save the results as "poi.txt" with the following format:
```
nodeID;pointType;pointName
```
The nodeID will correspond to the ID of the node where that point is located. 

## Project Members
 * [Caramelo18](https://github.com/Caramelo18)
 * [DiogoMCampos](https://github.com/DiogoMCampos)
 * [williamnf](https://github.com/williamnf)

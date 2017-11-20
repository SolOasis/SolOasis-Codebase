# SolOasis-Codebase
Codebase for entire SolOasis senior design project

## Test

The API server is deployed on [https://desolate-depths-35197.herokuapp.com/SolOasis/api/v1.0/update/]

Use POST method with json data to update battery percentage.

For example (using curl on Linxu):
```
 curl -H "Content-Type: application/json" -X POST -d '{"ID":0,"data":{"percentage":40}}' https://desolate-depths-35197.herokuapp.com/SolOasis/api/v1.0/update/
```
The json data would be like 
{"ID": (ID of the SolOasis Station),
 "data": (data in dictionary)}



## Authors

Chris
Ya-Liang Chang (Allen) [amjltc295]("https://github.com/amjltc295")

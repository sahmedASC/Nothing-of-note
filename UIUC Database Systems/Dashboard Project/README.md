
### Title
Data Scientist Dashboard

### Purpose
The dashboard supports data-driven decisions in the world of academia. The widgets work together to provide the data scientist a comprehensive, multi-level view of the university's research landscape. The keyword analysis widgets provide a high-level perspective, while the location and publication widgets allow zooming in on more specific details. Collectively, the widgets support the data scientist in exploring broad research patterns and trends, identifying pockets of expertise, and connecting research topics to specific campuses, departments, and individuals. These multidimensional views together enable efficient and multidimensional analysis.

The above analysis is complex to perform due to the vast variety of features in the Academic World dataset. It also requires a certain level of domain as well as statistical expertise. 

A dashboard like this will save considerable time of the data scientist by providing the latest and accurate information even when new data becomes available. The data scientist can now focus on researching and optimizing models and doesn’t have to spin up jupyter notebooks for complex Exploratory Data Analysis. 

### Target users
Data scientists working in a university’s research administration. Their role is to derive insights from different areas of academia to support strategic decision making.

### Installation

pip install -r requirements.txt 

### Usage

python app.py

Click on the browser link to view the dashboard

### Design
#### Overview
The application is a web based dashboard that has multiple widgets serving a variety of functionalities that support the data scientist persona. These widgets call 3 databases in the backend those being MySQL, MongoDB, and Neo4j.
#### Dashboard components: 
python file app.py, which uses dash, dash-bootstrap-components and Pandas to declaratively create widgets and their layout.

#### Database access components:
python functions organized in files mysql_utils.py, mongodb_utils.py, and neo4j_utils.py to access the mySQL, mongodb and neo4j databases using their query languages via their python package network interfaces to support the widgets. 

### Implementation

#### Frontend frameworks:
Dash, Dash-bootstrap-components, Plotly, Pandas
#### Backend frameworks: 
GraphDatabase (neo4j),
connector (mysql),
pymongo (mongoDB),
Pandas
### Database Techniques

- Trigger (widget #6) </br>
- Stored procedure (widget #6) 
<br>
<i>When a user wants to add a keyword to the database. 
First a <b>stored procedure</b> runs which generates a unique id for this new keyword and inserts the keyword.
<br>Before the INSERT there is a <b>trigger</b> that checks the keyword name. If the user is trying to insert a keyword name that already exists, it prevents that from happening.
The user made keyword is now added to the database. An "insert successful" string is returned and displayed on the widget.
These techniques preserve the data integrity of the keyword table so that every unique id in the keyword table leads to a unique name of a keyword. </i>


- View (widget #5)
<br>
<i>For every keyword and it's score in publication keyword table, the keyword score is normalized and top 20 keywords are returned. This query is saved as a view and abstracts away the statistical complexities of normalizing data and aggregating the query </i>

### Extra-credit capabilities

- Multi-database querying: <br>
Function fetches list of universities from mySQL. Once a user selects a university, the top 5 keywords are displayed by querying Neo4j  i.e., uses the result from querying MySQL to query Neo4j (widget #1) <br>
- Data expansion: <br> Added geographic locations of universities to widget #3. This allows the user to account for geospatial attributes in their analysis. <br>
- Data cleaning: <br> Interactively update publication metadata by allowing user to adjust values in the backend to ensure data quality. The widget finds errors in publication metadata for e.g. title and makes necessary corrections (widget #4) <br>


### ** Data Exploration Widget: Top Keywords in University with Insert & Delete functionality <br> (Left, widgets #1 and #6 ) **
![Example Image](widget_pics/widgets_1_and_6.png)

#### Purpose: 
Widget #1 enables curation and analysis of keywords within a publication that represent the selected university’s research focus. It helps the data scientist quickly identify the main research themes and topics the university specializes in. Widget #6 serves the purpose of keeping the database up to date by allowing insertion of new keywords and removal of irrelevant/outdated keywords.
#### How it works: 
The user selects a university of interest and top 5 keywords are displayed (widget #1). The user can also insert and remove keywords to keep the datasets up-to-date, reflecting current research priorities (widget #6).
<br></br>
### ** Trend Analysis Widget: Top Keywords in Year Range (Right, widget #2) **
![Example Image](widget_pics/widget_2.png)
#### Purpose: 
This widget identifies and visualizes shifts in research keyword prominence over selected time spans.
#### How it works: 
The user performs trend analysis by adjusting the timeline to extract and visualize data on historical and emerging trends in research topics to predict and recommend future funding areas.
<br></br>
### ** Geographic Distribution Widget: University Locations (Center, widget #3) **
![Example Image](widget_pics/widget_3.png)
#### Purpose: 
Geospatial analysis of university distribution within the United States helps identify university locations. It also helps inform decisions on research initiatives and collaborations across different states.
#### How it works: 
The user hovers over the interactive map to visualize, understand and report on the density and location of universities. They can further select the university of interest and use widget #1 to find popular research topics across the country by location.
<br></br>
### ** Publication Management Widget: Faculty Publications (below Center, widget #4) **
![Example Image](widget_pics/widget_4.png)
#### Purpose: 
This widget manages and queries publication metadata for faculty from a particular university to analyze the impact of a given faculty member. For e.g. updating citation counts post-conference season reflects the increased academic impact and visibility of our faculty’s research.This widget also serves the purpose of ensuring data quality. Within a query, if any discrepancy is observed in any of the metadata such as title, venue, year or number of citations, the corrections can be easily made via the dashboard in the backend database.
#### How it works: 
The user selects a university and faculty member from the drop down menu. A publication table is displayed with the option to update the table data.
<br></br>
### ** Keyword Impact Widget: Keyword Score Table (Bottom most, widget #5) **
![Example Image](widget_pics/widget_5.png)
#### Purpose: 
This widget evaluates the relevance of research keywords based on normalized scoring where the scores were normalized between 0 and 1. This is a typical statistical technique used by data scientists to determine impact using a standard scale. Outputs from this widget helps the data scientist analyze and determine which cutting-edge topics should be included in the curriculum for a degree program in data science.
#### How it works: 
A bar chart of normalized keyword scores is displayed with Keywords on x-axis and normalized scores between 0 and 1 on y-axis.
<br></br>

### Contributions

| Task                                        | Time Spent | Performed by |
|---------------------------------------------|------------|--------------|
| Design and create frontend widgets          | 20 hours   | Kinara       |
| Create backend queries and connection to databases | 20 hours   | Saaif        |
| Create README.md                            | 6 hours    | Kinara       |
| Test the app locally and record video demo  | 3 hours    | Saaif        |
| Discuss overall theme and architecture of the project | 4 hours    | Both         |

<br></br>
### Demo

Demo Link



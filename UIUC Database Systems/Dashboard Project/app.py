import pandas as pd
import plotly.graph_objects as go
import plotly.express as px

from dash import Dash, Input, Output, State, dcc, html, no_update, dash_table, ALL, ctx
import dash_bootstrap_components as dbc
from dash.exceptions import PreventUpdate

from neo4j_utils import get_top_five_keywords
import mysql.connector
from mongodb_utils import get_keywords_time_range, fetch_faculty_names, fetch_publications_for_faculty, update_publication_backend
from mysql_utils import insert_keyword, delete_keyword, get_unique_university_names, apply_trigger, apply_stored_procedure, create_normalized_keyword_scores_view, fetch_top_20_normalized_scores

import logging

logging.basicConfig(level="DEBUG", format=" %(levelname)s:%(funcName)s:%(message)s")

logger = logging.getLogger(__name__)
logger.info("=" * 80)

# --------------------------------------------------------------------------------
# Create a connection to your MySQL database
conn = mysql.connector.connect(
    host="127.0.0.1", user="root", password="test_root", database="academicworld"
)
cursor = conn.cursor()

apply_trigger(conn)
apply_stored_procedure(conn)
create_normalized_keyword_scores_view(conn)

# ---------------------------------------------------------------------------------
# FUNCTIONS TO FETCH DATA FROM DATABASE

def get_keywords_year_range():
    return [1980, 2020]

# ----------------------------------------------------------------------------------

app = Dash(external_stylesheets=[dbc.themes.BOOTSTRAP])

# =================================================================================
# LAYOUT

# ---------------------------------------------------------------------------------

hr_style = {
    "height": "5px",
    "background-color": "black",
    "border": "none",
    "margin": "0",
}

keywords_year_range = get_keywords_year_range()

university_names = get_unique_university_names(conn)
# ---------------------------------------------------------------------------------

# dropdown to select university name and display the top keywords in it
widget_1 = dbc.Card(
    [
        dbc.CardHeader("Top Keywords in University", style={"font-weight": "bold"}),
        dbc.CardBody(
            [
                dbc.Label("Select University :"),
                dcc.Dropdown(
                    id="university-names-dropdown",
                    options=[{"label": uni, "value": uni} for uni in university_names],
                    value=university_names[0],
                ),
                html.Br(),
                html.H6("Top Keywords"),
                html.Div(id="top-keywords"),
            ],
            style={"padding": "8px"},
        ),
    ],
    style={"border-width": "2px", "border-style": "solid"},
)

# slider to select a year range and show top 10 keywords and their scores
widget_2 = dbc.Card(
    [
        dbc.CardHeader("Top Keywords in Year Range", style={"font-weight": "bold"}),
        dbc.CardBody(
            [
                dbc.Label("Select Year Range :"),
                dcc.RangeSlider(
                    id="keyword-year-range-slider",
                    min=keywords_year_range[0],
                    max=keywords_year_range[1],
                    step=1,
                    marks={
                        i: str(i)
                        for i in range(
                            keywords_year_range[0], keywords_year_range[1] + 1, 2
                        )
                    },
                    tooltip={"placement": "top", "always_visible": True},
                ),
                html.Br(),
                dcc.Graph(id="keyword-year-range-graph"),
            ]
        ),
    ],
    style={"border-width": "2px", "border-style": "solid"},
)

# Insert/Delete keywords
widget_3 = dbc.Card(
    [
        dbc.CardHeader("Keywords", style={"font-weight": "bold"}),
        dbc.CardBody(
            [
                dbc.Label("Insert Keyword :"),
                dbc.Input(
                    id="insert-keyword", type="text", placeholder="Enter keyword"
                ),
                html.Br(),
                dbc.Row(
                    [
                        dbc.Col(
                            dbc.Button("Insert", color="primary", id="insert-button"),
                            width="auto",
                        ),
                        dbc.Col(
                            dbc.Alert(
                                "Inserted",
                                color="success",
                                id="insert-alert",
                                is_open=False,
                                dismissable=True,
                            ),
                            width="auto",
                        ),
                    ],
                ),
            ],
            style={"padding": "8px"},
        ),
        html.Hr(style={"margin": "0"}),
        dbc.CardBody(
            [
                dbc.Label("Delete Keyword :"),
                dbc.Input(
                    id="delete-keyword", type="text", placeholder="Enter keyword"
                ),
                html.Br(),
                dbc.Row(
                    [
                        dbc.Col(
                            dbc.Button("Delete", color="danger", id="delete-button"),
                            width="auto",
                        ),
                        dbc.Col(
                            dbc.Alert(
                                "Deleted",
                                color="success",
                                id="delete-alert",
                                is_open=False,
                                dismissable=True,
                            ),
                            width="auto",
                        ),
                    ],
                ),
            ],
            style={"padding": "8px"},
        ),
    ],
    style={"border-width": "2px", "border-style": "solid"},
)

widget_4_cardbody = dbc.CardBody(
    [
        dbc.Row(
            [
                dbc.Col(
                    [
                        dbc.Label("Select University :"),
                        dcc.Dropdown(
                            id="widget4-university-names-dropdown",
                            options=[
                                {"label": uni, "value": uni} for uni in university_names
                            ],
                            value=university_names[0],
                        ),
                        html.Br(),
                        dbc.Label("Select Faculty :"),
                        dcc.Dropdown(
                            id="widget4-faculty-names-dropdown",
                            options=list(),
                        ),
                    ],
                    width=3,
                ),
                dbc.Col(
                    [
                        dbc.Label("Publications Table :"),
                        dash_table.DataTable(
                            id="widget4-publications-table",
                            columns=[
                                {"name": "id", "id": "id"},
                                {"name": "title", "id": "title"},
                                {"name": "venue", "id": "venue"},
                                {"name": "year", "id": "year"},
                                {"name": "numCitations", "id": "numCitations"},
                            ],
                            style_table={"overflowX": "auto"},
                            style_cell={"textAlign": "left"},
                        ),
                    ],
                    width=5,
                ),
                # label input pairs to input publication details for new row in the table
                dbc.Col(
                    [
                        dbc.Label("ID :"),
                        dbc.Input(
                            id="publication-id-input",
                            type="number",
                            placeholder="Enter id",
                        ),
                        dbc.Label("Title :"),
                        dbc.Input(
                            id="publication-title-input",
                            type="text",
                            placeholder="Enter title",
                        ),
                        dbc.Label("Venue :"),
                        dbc.Input(
                            id="publication-venue-input",
                            type="text",
                            placeholder="Enter venue",
                        ),
                        dbc.Label("Year :"),
                        dbc.Input(
                            id="publication-year-input",
                            type="number",
                            placeholder="Enter year",
                        ),
                        dbc.Label("Num Citations :"),
                        dbc.Input(
                            id="publication-num-citations-input",
                            type="number",
                            placeholder="Enter num citations",
                        ),
                        html.Br(),
                        dbc.Button(
                            "Update publication",
                            color="primary",
                            id="update-publication-button",
                        ),
                    ],
                    width=4,
                ),
            ]
        ),
    ],
    style={"padding": "8px"},
)

# select uni-> faculty -> publications table
widget_4 = dbc.Card(
    [
        dbc.CardHeader("Faculty Publications", style={"font-weight": "bold"}),
        widget_4_cardbody,
    ],
    style={"border-width": "2px", "border-style": "solid"},
)


# ---------------------------------------------------------------------------------
# widget 5

# TODO - replace with database function
keyword_scores = fetch_top_20_normalized_scores(conn)
view_x_axis = keyword_scores['keyword_name']
view_y_axis = keyword_scores['normalized_score']

fig = go.Figure()
fig.add_trace(
    go.Bar(
        x=list(view_x_axis),
        y=list(view_y_axis),
        # orientation="h",
        marker_color='green'
    )
)
fig.update_layout(
    title=f"Keyword Normalized Scores",
    xaxis_title="Keywords",
    yaxis_title="Scores",
)


widget_5 = dbc.Card(
    [
        dbc.CardHeader("Keyword Normalized Scores", style={"font-weight": "bold"}),
        dbc.CardBody(
            [
                dcc.Graph(figure=fig, id="widget5-graph"),
            ],
            style={"padding": "8px"},
        ),
    ],
    style={"border-width": "2px", "border-style": "solid"},
)

# ---------------------------------------------------------------------------------


from utils import university_locations

university_locations = pd.DataFrame(
    university_locations.items(), columns=["state", "universities"]
)
university_locations["uni_count"] = university_locations["universities"].apply(
    lambda x: len(x)
)


def f(list_of_uni):
    hover_val = "<br>"
    for uni in list_of_uni:
        hover_val += uni + "<br>"
    return hover_val


university_locations["universities"] = university_locations["universities"].apply(f)


uni_map = px.choropleth(
    university_locations,
    locations="state",
    locationmode="USA-states",
    scope="usa",
    hover_data="universities",
    color="uni_count",
    title="<b>University Locations</b>",
)
uni_map.update_layout(title_x=0.5)

# remove margin
uni_map.update_layout(margin={"r": 0, "l": 0, "b": 0})

app.layout = dbc.Container(
    fluid=True,
    children=[
        dcc.Store(id="widget4-publications-table-data-store"),
        html.H4(
            "DATA SCIENTIST DASHBOARD",
            style={"text-align": "center", "color": "darkgreen"},
        ),
        html.Hr(style=hr_style),
        html.Br(),
        dbc.Row(
            [
                dbc.Col(
                    [widget_1, html.Div(style={"height": "10px"}), widget_3], width=4
                ),
                dbc.Col(widget_2, width=8),
            ]
        ),
        html.Br(),
        dcc.Graph(figure=uni_map, id="uni-map-graph"),
        html.Br(),
        dbc.Row(
            [
                dbc.Col(widget_4),
            ]
        ),
        html.Br(),
        dbc.Row(
            [
                dbc.Col(widget_5),
            ]
        ),
    ],
    style={"backgroundColor": "Lavender"},
)


# =================================================================================
# CALLBACKS


# widget 1
# Get top keywords for selected university
@app.callback(
    Output("top-keywords", "children"),
    Input("university-names-dropdown", "value"),
)
def update_top_keywords(uni_name):

    if uni_name is None:
        raise PreventUpdate

    logger.info(f"Selected University: {uni_name}")

    keywords = get_top_five_keywords(uni_name)
    keywords = keywords['Keyword']


    return html.Ul([html.Li(word) for word in keywords])


# widget 2
# Get top keywords for selected year range
@app.callback(
    Output("keyword-year-range-graph", "figure"),
    Input("keyword-year-range-slider", "value"),
)
def update_keyword_year_range_graph(year_range):

    if year_range is None:
        raise PreventUpdate

    logger.info(f"Selected Year Range: {year_range}")

    keyword_scores_df = get_keywords_time_range(year_range[0], year_range[1])
    keyword_scores_df = keyword_scores_df.sort_values(by="score", ascending=False)
    keyword_scores_df = keyword_scores_df.head(10)

    keyword_names = keyword_scores_df["name"].tolist()
    keyword_scores_list = keyword_scores_df["score"].tolist()
    keyword_scores = {}
    for name, score in zip(keyword_names, keyword_scores_list):
        keyword_scores[name] = score
    print(keyword_scores)

    # horizontal bar chart
    fig = go.Figure()
    fig.add_trace(
        go.Bar(
            x=list(keyword_scores.values()),
            y=list(keyword_scores.keys()),
            orientation="h",
        )
    )
    fig.update_layout(
        title=f"Top Keywords in Year Range {year_range[0]} - {year_range[1]}",
        xaxis_title="Scores",
        yaxis_title="Keywords",
    )
    return fig


# widget 3
# insert keyword
@app.callback(
    Output("insert-alert", "is_open"),
    Output("insert-alert", "children"),
    Input("insert-button", "n_clicks"),
    State("insert-keyword", "value"),
)
def insert_keyword_callback(n_clicks, keyword):

    if n_clicks is None:
        raise PreventUpdate

    if keyword is None or keyword == "":
        raise PreventUpdate

    logger.info(f"Inserting keyword: {keyword}")

    message = insert_keyword(conn, keyword)

    return True, message


# delete keyword
@app.callback(
    Output("delete-alert", "is_open"),
    Input("delete-button", "n_clicks"),
    State("delete-keyword", "value"),
)
def delete_keyword_callback(n_clicks, keyword):

    if n_clicks is None:
        raise PreventUpdate

    if keyword is None or keyword == "":
        raise PreventUpdate

    logger.info(f"Deleting keyword: {keyword}")

    # TODO - replace with database function
    delete_keyword(conn, keyword)

    return True


# widget 4
# get faculty names based on selected university
@app.callback(
    Output("widget4-faculty-names-dropdown", "options"),
    Input("widget4-university-names-dropdown", "value"),
)
def update_faculty_names_dropdown(uni_name):

    if uni_name is None:
        raise PreventUpdate

    logger.info(f"Selected University: {uni_name}")

    # TODO - replace with database function
    #faculty_names = ["Faculty 1", "Faculty 2", "Faculty 3"]
    faculty_names = fetch_faculty_names(uni_name)[:10]

    return [{"label": faculty, "value": faculty} for faculty in faculty_names]


# get publications based on selected faculty
@app.callback(
    Output("widget4-publications-table-data-store", "data"),
    Input("widget4-faculty-names-dropdown", "value"),
)
def update_publications_table(faculty_name):

    if faculty_name is None:
        raise PreventUpdate

    logger.info(f"Selected Faculty: {faculty_name}")


    publications = fetch_publications_for_faculty(faculty_name)
    publications = publications.to_dict(orient="records")

    return publications


# update publications table from the store
@app.callback(
    Output("widget4-publications-table", "data"),
    Input("widget4-publications-table-data-store", "data"),
)
def update_publications_table_from_store(data):

    if data is None:
        raise PreventUpdate

    return data


# update publication from the input fields
@app.callback(
    Output("widget4-publications-table-data-store", "data", allow_duplicate=True),
    Input("update-publication-button", "n_clicks"),
    State("publication-id-input", "value"),
    State("publication-title-input", "value"),
    State("publication-venue-input", "value"),
    State("publication-year-input", "value"),
    State("publication-num-citations-input", "value"),
    State("widget4-publications-table-data-store", "data"),
    prevent_initial_call=True,
)
def update_publication(n_clicks, id, title, venue, year, num_citations, data_store):

    if n_clicks is None:
        raise PreventUpdate

    for val in [id, title, venue, year, num_citations]:
        if val is None:
            raise PreventUpdate

    logger.info(f"Updating publication with id: {id}")

    update_publication_backend(id, title, venue, year, num_citations)

    for publication in data_store:
        if publication["id"] == id:
            publication.update(
                {
                    "id": id,
                    "title": title,
                    "venue": venue,
                    "year": year,
                    "numCitations": num_citations,
                }
            )
            break

    return data_store


if __name__ == "__main__":
    app.run(debug=True)

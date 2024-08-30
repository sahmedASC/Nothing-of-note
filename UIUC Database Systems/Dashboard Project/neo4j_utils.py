from neo4j import GraphDatabase
import pandas as pd

#NOTE: you will need to reset the academicworld database password to this password in neo4j
uri = "bolt://localhost"  # Neo4j URL
username = "neo4j"      # username
password = "ilovecs411"      # password

def get_top_five_keywords(university_name):
    '''
    Fetch top 5 KW scores from papers of that university
    :param university_name: the input name of the university entered by the user
    :return: a dataframe with columns [Keyword, TotalScore] with the result of the query
    '''

    query = """
        MATCH (uiuc:INSTITUTE {name: $universityName})<-[:AFFILIATION_WITH]-(uiuc_faculty:FACULTY)-[:PUBLISH]->(p:PUBLICATION)-[r:LABEL_BY]->(k:KEYWORD)
        RETURN k.name AS Keyword, SUM(r.score) AS TotalScore
        ORDER BY TotalScore DESC
        LIMIT 5
        """
    params = {"universityName": university_name}

    with GraphDatabase.driver(uri, auth=(username, password)) as driver:
        with driver.session(database="academicworld") as session:
            result = session.run(query,params)
            records = [record for record in result]
            df = pd.DataFrame([dict(record) for record in records])
            return df

if __name__ == '__main__':
    uni = "University of illinois at Urbana Champaign"
    print(get_top_five_keywords(uni))

    #driver.close()

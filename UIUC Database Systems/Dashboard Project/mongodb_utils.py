import pymongo
import pandas as pd

# MongoDB's connection details
host = "localhost"
port = 27017

def get_keywords_time_range(start, end):
    '''
    Gets the unique keywords that are not null within a year time period.
    :param start: start year
    :param end: end year
    :return:a dataframe of [id, name, score] that is unique
    '''

    query = {
        "year": {"$gte": start, "$lte": end},
        "keywords": {"$ne": []}  # Exclude documents where keywords array is empty
    }
    projection = {
        "_id": 0,
        "keywords": 1
    }
    client = pymongo.MongoClient(host, port)

    db = client["academicworld"]
    results = db.publications.find(query, projection)

    unique_keyword_names = set()
    unique_keywords = []

    # Iterate and extract unique keywords
    for result in results:
        for keyword in result.get("keywords", []):
            keyword_id = keyword.get("id")
            keyword_name = keyword.get("name")
            keyword_score = keyword.get("score")

            # Ensure keyword is not empty and is unique
            if keyword_id and keyword_name and keyword_score and (keyword_name not in unique_keyword_names):
                unique_keyword_names.add(keyword_name)
                unique_keywords.append({
                    "id": keyword_id,
                    "name": keyword_name,
                    "score": keyword_score
                })
    df = pd.DataFrame(unique_keywords)
    client.close()
    return df

def fetch_faculty_names(uni_name):
    '''
    :return: Returns a list of every faculty name in the mongoDB database
    '''
    client = pymongo.MongoClient(host, port)
    db = client["academicworld"]

    cursor = db.faculty.find({"affiliation.name": uni_name}, {"name": 1, "_id": 0})
    faculty_names = [doc["name"] for doc in cursor]

    client.close()
    return faculty_names

def fetch_publications_for_faculty(faculty_name):
    '''
    For a given faculty name, return 10 of their publications
    :param faculty_name: name of faculty member
    :return: pandas dataframe of 10 publications by the faculty member
    '''
    client = pymongo.MongoClient(host, port)
    db = client["academicworld"]

    faculty_document = db.faculty.find_one({"name": faculty_name})
    if not faculty_document:
        print(f"No faculty found with the name '{faculty_name}'")
        return None

    # Get the publication IDs
    publication_ids = faculty_document.get("publications", [])[:10]  # Get first 10 publications

    publication_cursor = db.publications.find({"id": {"$in": publication_ids}}, {"_id": 0, "title": 1, "id": 1, "venue": 1, "year": 1, "numCitations": 1})
    publication_list = list(publication_cursor)

    df = pd.DataFrame(publication_list)
    client.close()
    return df

def capitalize_publication_name(publication_id):
    '''
    For a given publication id, capitalize its title.
    :param publication_id: publication to be capitalized
    :return: None, capitalizes the publication title.
    '''
    client = pymongo.MongoClient(host, port)
    db = client["academicworld"]

    publication_document = db.publications.find_one({"id": publication_id})
    if not publication_document:
        print(f"No publication found with the ID '{publication_id}'")
        return

    publication_name = publication_document.get("title", "")
    capitalized_publication_name = publication_name.capitalize()

    db.publications.update_one(
        {"id": publication_id},
        {"$set": {"title":capitalized_publication_name }}
    )

    client.close()
    print(f"Publication '{publication_name}' with ID '{publication_id}' updated to '{capitalized_publication_name}'")

def update_publication_backend(id, title, venue, year, num_citations):
    client = pymongo.MongoClient(host, port)

    db = client['academicworld']
    collection = db['publications']

    result = collection.update_one(
        {"id": id},
        {"$set": {
            "title": title,
            "venue": venue,
            "year": year,
            "numCitations": num_citations
        }}
    )
    client.close()

    if result.modified_count == 1:
        print(f"Publication with ID '{id}' updated successfully.")
    else:
        print(f"No publication found with ID '{id}'. No update performed.")

if __name__ == "__main__":
    faculty_name = "Chaparro,Oscar"
    publications_df = fetch_publications_for_faculty(faculty_name)
    if publications_df is not None:
        print(publications_df)

    publication_id = 3101622575
    capitalize_publication_name(publication_id)

    publications_df = fetch_publications_for_faculty(faculty_name)
    if publications_df is not None:
        print(publications_df)
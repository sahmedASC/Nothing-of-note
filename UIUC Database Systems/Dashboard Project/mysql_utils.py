import mysql.connector
import pandas as pd

def get_keyword_list_threshold(conn,score_threshold):
    '''
    Get a list of keywords that are less than the threshold
    :param score_threshold: the user input
    :return: df as a result of the query.
    '''
    cursor = conn.cursor()

    query = """
    SELECT k.id, k.name, fk.score
    FROM keyword AS k
    JOIN faculty_keyword AS fk ON k.id = fk.keyword_id
    WHERE fk.score < %s
    """
    #execute
    cursor.execute(query, (score_threshold,))
    keyword_scores = cursor.fetchall()
    df = pd.DataFrame(keyword_scores, columns=['id', 'keyword', 'score'])

    cursor.close()
    return df


def delete_keyword(conn, name_value):
    '''
    Delete a keyword entry from the 'keyword' table based on id and name.
    :param name_value: The name of the keyword to delete.
    :return: None. The function deletes the entry from the 'keyword' table.
    '''
    cursor = conn.cursor()

    cursor.execute("SET FOREIGN_KEY_CHECKS=0")

    delete_query = """
    DELETE FROM keyword
    WHERE name = %s
    """
    cursor.execute(delete_query, (name_value,))
    conn.commit()

    cursor.execute("SET FOREIGN_KEY_CHECKS=1")
    cursor.close()

def insert_keyword(conn, keyword_name):
    '''
    Insert a new row into the 'keyword' table with id, name, and score.
    :param conn: MySql Connection
    :param name_value: The name of the keyword.
    :return: The function inserts a new row into the 'keyword' table. Success or Failure Message to be displayed
    '''

    cursor = conn.cursor()
    try:
        # Generate a unique ID
        keyword_id = cursor.callproc('generate_keyword_id', (0,))
        if keyword_id[0] is not None:
            insert_query = "INSERT INTO keyword (id, name) VALUES (%s, %s)"

            cursor.execute(insert_query, (keyword_id[0], keyword_name))
            conn.commit()
            cursor.close()
            return "Keyword inserted successfully"
        else:
            return "Failed to generate keyword ID"
    except mysql.connector.Error as err:
        cursor.close()
        return f"Error inserting keyword: {err}"

def get_unique_university_names(conn):
    '''
    Get a unique list of university names from the 'university' table.
    :param conn: MySQL database connection.
    :return: A list of unique university names.
    '''
    cursor = conn.cursor()
    query = "SELECT DISTINCT name FROM university;"
    cursor.execute(query)

    rows = cursor.fetchall()
    unique_names = [row[0] for row in rows]
    cursor.close()
    return unique_names

def apply_trigger(conn):
    '''
    MUST BE RUN AT APP STARTUP
    Creates a trigger on the sql database when a keyword is inserted. Prevents duplicate keyword names from insertion.
    :param conn: The MySql connection
    :return: Success or failure message
    '''
    cursor = conn.cursor()
    # Check if the trigger exists
    cursor.execute("SHOW TRIGGERS")
    existing_trigger = cursor.fetchone()

    if existing_trigger:
        print("Trigger 'keyword_insert_trigger' already exists")
        cursor.close()
    else:
        # Define the trigger
        trigger_sql = """
            CREATE TRIGGER keyword_insert_trigger
            BEFORE INSERT ON keyword
            FOR EACH ROW
            BEGIN
                DECLARE keyword_count INT;

                SELECT COUNT(*) INTO keyword_count
                FROM keyword
                WHERE name = NEW.name;

                IF keyword_count > 0 THEN
                    SIGNAL SQLSTATE '45000' 
                    SET MESSAGE_TEXT = 'Error: Keyword name must be unique';
                END IF;
            END;
            """

        cursor.execute(trigger_sql)
        print("Trigger 'keyword_insert_trigger' created successfully")
        conn.commit()
        cursor.close()


def apply_stored_procedure(conn):
    '''
    MUST BE RUN AT APP STARTUP
    Adds a stored procedure that generates a unique id for the keyword INSERT function.
    :param conn: MySql connection
    :return: Success or failure message
    '''
    cursor = conn.cursor()
    # Check if the stored procedure exists
    cursor.execute("SHOW PROCEDURE STATUS WHERE Db = 'academicworld' AND Name = 'generate_keyword_id'")
    existing_procedure = cursor.fetchone()

    if existing_procedure:
        print("Stored procedure 'generate_keyword_id' already exists")
    else:
        # Define the stored procedure
        stored_procedure_sql = """
            CREATE PROCEDURE generate_keyword_id(INOUT keyword_id INT)
            BEGIN
                SELECT COALESCE(MAX(id), 0) + 1 INTO keyword_id FROM keyword;
            END;
            """
        cursor.execute(stored_procedure_sql)
        conn.commit()
        print("Stored procedure 'generate_keyword_id' created successfully")

    cursor.close()

def create_normalized_keyword_scores_view(conn):
    cursor = conn.cursor()
    try:
        cursor.execute("SHOW TABLES LIKE 'normalized_keyword_scores'")
        if cursor.fetchone():
            print("View 'normalized_keyword_scores' already exists.")
            cursor.close()
            return

        # Create  view
        create_view_query = """
            CREATE VIEW normalized_keyword_scores AS
            SELECT pk.keyword_id, k.name AS keyword_name, pk.score / max_score AS normalized_score
            FROM publication_keyword pk
            JOIN (
                SELECT MAX(score) AS max_score
                FROM publication_keyword
            ) AS max_scores ON 1=1
            JOIN keyword k ON pk.keyword_id = k.id
            ORDER BY normalized_score DESC
            """
        cursor.execute(create_view_query)
        conn.commit()

    except mysql.connector.Error as err:
        print(f"Error creating/view: {err}")
        cursor.close()
        return None
    cursor.close()

def fetch_top_20_normalized_scores(conn):
    cursor = conn.cursor()
    try:
        # Fetch the top 20
        cursor.execute("SELECT * FROM normalized_keyword_scores LIMIT 20")
        top_20_rows = cursor.fetchall()

        df = pd.DataFrame(top_20_rows, columns=['keyword_id', 'keyword_name', 'normalized_score'])
        df = df.drop_duplicates(subset=['keyword_name'], keep='last')
        cursor.close()
        return df
    except mysql.connector.Error as err:
        print(f"Error fetching top 20 rows: {err}")
        cursor.close()
        return None

if __name__ == '__main__':
    conn = mysql.connector.connect(
        host='127.0.0.1',
        user='root',
        password='test_root',
        database='academicworld'
    )
    queryResult = get_keyword_list_threshold(conn,1)
    print(queryResult)
    # update_keyword_scores_by_id(conn,9,0)
    # queryResult = get_keyword_list_threshold(conn, 1)
    # print(queryResult)

    # unique_universities = get_unique_university_names(conn)
    # print(unique_universities)
    apply_trigger(conn)

    apply_stored_procedure(conn)

    #print(insert_keyword(conn, "security"))
    print(insert_keyword(conn,"testKeyword0"))

    create_normalized_keyword_scores_view(conn)
    print(fetch_top_20_normalized_scores(conn))

    conn.close()




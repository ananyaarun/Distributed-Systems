from google.cloud import bigquery

def func1():
    print("enter userID and K")
    client = bigquery.Client()
    a = input()
    b = input()
    query = """
        SELECT * FROM `assg25559.test.tableanan`
        WHERE userID = @para1
        ORDER BY viewCount DESC
        LIMIT @para2;
        """
    job_config = bigquery.QueryJobConfig(
        query_parameters=[
            bigquery.ScalarQueryParameter("para1", "INT64", a),
            bigquery.ScalarQueryParameter("para2", "INT64", b),
        ]
    )
    query_job = client.query(query, job_config=job_config)
    rows = query_job.result()
    for row in rows:
        print(row.itemID)




def func2():
    print("enter itemID")
    client = bigquery.Client()
    a = input()
    # Perform a query.
    query = """
        SELECT COUNT(DISTINCT userID) AS tot FROM `assg25559.test.tableanan`
        WHERE itemID = @para;
        """
    job_config = bigquery.QueryJobConfig(
        query_parameters=[
            bigquery.ScalarQueryParameter("para", "INT64", a),
        ]
    )
    query_job = client.query(query, job_config=job_config)  # API request
    rows = query_job.result()  # Waits for query to finish
    for r in rows:
        print(r.tot)




def func3():
    client = bigquery.Client()
    print("enter itemID and K")
    a = input()
    b = input()
    query = """
        SELECT * FROM `assg25559.test.tableanan`
        WHERE userID IN (SELECT userID FROM `assg25559.test.tableanan` WHERE itemID = @para1)
        ORDER BY userID , viewCount DESC ;
        """
    job_config = bigquery.QueryJobConfig(
        query_parameters = [
            bigquery.ScalarQueryParameter("para1", "INT64", a),
        ]
    )
    query_job = client.query(query, job_config=job_config)  # API request
    rows = query_job.result()  # Waits for query to finish
    prev = -1
    chk = 1
    ct = 0
    for row in rows:
        if chk == 1:
            print("{} : {}".format(row.userID, row.itemID))
            ct += 1
        if prev != -1:
            if str(row.userID) != str(prev):
                chk = 1
        if int(ct) >= int(b):
            chk = 0
            ct = 0
        prev = row.userID




def func4():

    client = bigquery.Client()
    print("enter itemID")
    a = input()
    # Perform a query.
    query = """
        SELECT SUM(viewCount) as sum FROM `assg25559.test.tableanan`
        WHERE itemID = @para;
        """
    job_config = bigquery.QueryJobConfig(
        query_parameters=[
            bigquery.ScalarQueryParameter("para", "INT64", a),
        ]
    )
    query_job = client.query(query, job_config=job_config)  # API request
    rows = query_job.result()  # Waits for query to finish
    for row in rows:
        print(row.sum)





def func5():

    client = bigquery.Client()

    # Perform a query.
    QUERY = (
            'SELECT COUNT(DISTINCT userID) as tot, itemID FROM `assg25559.test.tableanan` '
            'GROUP BY itemID '
            'ORDER by tot DESC '
            'LIMIT 1'
            )

    query_job = client.query(QUERY)  # API request
    rows = query_job.result()  # Waits for query to finish

    for row in rows:
        print(row.itemID)





if __name__ == '__main__':

    loop = 1
    choice = 0
    while loop == 1:
        print("Pick the query you want to run - ")
        print("1) top(userID, K)")
        print("2) interested(itemID)")
        print("3) top_interested(itemID, K)")
        print("4) view_count(userID)")
        print("5) popular()")
        choice = input()

        if str(choice) == "1":
            func1()
        elif str(choice) == "2":
            func2()
        elif str(choice) == "3":
            func3()
        elif str(choice) == "4":
            func4()
        elif str(choice) == "5":
            func5()
        elif str(choice) == "0":
            loop = 0
# Install deterministic file-table fixtures in the observer working directory.
# The seekdb evaluation runs mysqltest and the observer on the same host, so the
# fixtures are installed with a local copy instead of ssh/scp (the observer data
# directory is OBSERVER_DIR, which the local filesystem can address directly).
connect (file_sql_setup,$OBMYSQL_MS0,admin,$OBMYSQL_PWD,test,$OBMYSQL_PORT);
connection file_sql_setup;

--disable_query_log
let $FILE_SQL_DATA_DIR = $OBSERVER_DIR/data_for_mysqltest_file_sql;
let $FILE_SQL_COPY_CMD = rm -rf "$FILE_SQL_DATA_DIR" && mkdir -p "$FILE_SQL_DATA_DIR" && cp -r mysql_test/test_suite/file_sql/data/* "$FILE_SQL_DATA_DIR/" && base64 -d "$FILE_SQL_DATA_DIR/simple.parquet.b64" > "$FILE_SQL_DATA_DIR/simple.parquet" && rm -f "$FILE_SQL_DATA_DIR/simple.parquet.b64";
exec $FILE_SQL_COPY_CMD;
--enable_query_log

disconnect file_sql_setup;
connection default;

get_duckdb_init_func <- function() {
  if (!requireNamespace("duckdb", quietly = TRUE)) {
    stop("Please install duckdb")
  }

  duckdb::duckdb_adbc()$driver_init_func
}

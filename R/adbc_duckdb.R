get_duckdb_dll_path <- function() {
  if (!requireNamespace("duckdb", quietly = TRUE)) {
    stop("Please install duckdb")
  }

  system.file(
    "libs",
    .Platform$r_arch,
    paste0("duckdb", .Platform$dynlib.ext),
    package = "duckdb"
  )
}

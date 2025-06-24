
#include <ogrsf_frmts.h>

#define RCPP_DEFAULT_INCLUDE_CALL false
#include "Rcpp.h"

#if GDAL_VERSION_NUM >= GDAL_COMPUTE_VERSION(3,11,0)
#include <gdal_adbc.h>

typedef uint8_t AdbcStatusCode;
typedef AdbcStatusCode (*AdbcDriverInitFunc)(int version, void* driver, void* error);

static uint8_t SfGDALADBCLoadDriver(const char *driver_name,
                                    const char *entrypoint, int version,
                                    void *driver, void *error) {
    if (strcmp(driver_name, "duckdb") != 0) {
        Rcpp::warning("The current ADBC driver only supports 'duckdb'");
        return 2; // ADBC_STATUS_NOT_IMPLEMENTED
    }

    Rcpp::Environment pkg = Rcpp::Environment::namespace_env("sf");
    Rcpp::Function get_duckdb_init_func = pkg["get_duckdb_init_func"];

    auto driver_init_func =
        reinterpret_cast<AdbcDriverInitFunc>(R_ExternalPtrAddrFn(get_duckdb_init_func()));
    return driver_init_func(version, driver, error);
}

#endif


// [[Rcpp::export]]
void CPL_init_adbc() {
#if GDAL_VERSION_NUM >= GDAL_COMPUTE_VERSION(3,11,0)
    GDALSetAdbcLoadDriverOverride(&SfGDALADBCLoadDriver);
#endif
}
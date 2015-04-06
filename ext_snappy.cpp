#include "hphp/runtime/base/base-includes.h"

/* snappy */
#include "snappy/snappy-c.h"
#include "snappy/snappy-version.h"

#include <string>

using namespace std;


namespace HPHP {
/////////////////////////////////////////////////////////////////////////////

String HHVM_FUNCTION(snappy_compress, const String& data) {
    size_t output_len;
	string out_std;

    output_len = snappy_max_compressed_length(data.length());

    out_std.resize(output_len);
    if (snappy_compress(data.c_str(), data.length(), (char*)out_std.c_str(), &output_len) == SNAPPY_OK) {
        out_std.resize(output_len);
    }

	return out_std;
}

String HHVM_FUNCTION(snappy_uncompress, const String& data) {
    size_t output_len;
	string out_std;


    if (snappy_uncompressed_length(data.c_str(), data.length(), &output_len) != SNAPPY_OK) {
        //zend_error(E_WARNING, "snappy_uncompress : output length error");
        return false;
    }

//    output = (char *)emalloc(output_len);
    out_std.resize(output_len);

//    if (!output) {
//        zend_error(E_WARNING, "snappy_uncompress : memory error");
//        RETURN_FALSE;
//    }

    if (snappy_uncompress(data.c_str(), data.length(), 
                          (char*)out_std.c_str(), &output_len) == SNAPPY_OK) {
		return out_std;
    } else {
       // zend_error(E_WARNING, "snappy_uncompress : data error");
       // RETVAL_FALSE;
		return false;
    }


}

class SnappyExtension : public Extension {
 public:
  SnappyExtension(): Extension("snappy", "0.1") {}

  void moduleInit() override {
    HHVM_FE(snappy_compress);
    HHVM_FE(snappy_uncompress);


    loadSystemlib();
  }
} s_snappy_extension;

HHVM_GET_MODULE(snappy);

/////////////////////////////////////////////////////////////////////////////
} // namespace HPHP

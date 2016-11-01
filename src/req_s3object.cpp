#include "req_s3object.h"

namespace Yacko {

    std::string getS3Object(request_rec *r)
    {
        std::string uri(r->uri);
        std::string handler_name = "yacko";
        std::string path = std::string(uri).substr(handler_name.length() + 2);
        int slashpos = path.find_first_of('/');
        std::string bucket = path.substr(0, slashpos);
        std::string objectkey = path.substr(slashpos + 1);

        std::shared_ptr < Aws::S3::S3Client > s3client = Yacko::getS3Client(r);
        Aws::S3::Model::GetObjectRequest getObjectRequest;
        getObjectRequest.SetBucket(bucket.c_str());
        getObjectRequest.SetKey(objectkey.c_str());

        auto getObjectOutcome = s3client->GetObject(getObjectRequest);
        if (!getObjectOutcome.IsSuccess()) {
            std::stringstream ss;
            ss << "File download failed from s3 with error " << getObjectOutcome.GetError().GetMessage();
            throw Yacko::internal_server_error(ss.str());
        }

        std::stringstream ss;
        ss << getObjectOutcome.GetResult().GetBody().rdbuf();
        return ss.str();
    }

}

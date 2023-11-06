//
// Created by disoz on 05.05.2023.
//
//  Doc: https://www.influxdata.com/blog/getting-started-c-influxdb/

#include <iostream>
#include <InfluxDBFactory.h>

int main(int argc, char *argv[]) {
//    auto db = influxdb::InfluxDBFactory::Get(
//            "http://localhost:8086?u=mAU0qSxYKxB5IGUSmYA2-A81llbagYJjoFSM-wJRQanijR3QBxqrZAZd4gd04HlC1RgqrKjd5x2gT5ICYTlOGQ==&db=R2H_Flight2&org=XSTRATO");
//    auto db = influxdb::InfluxDBFactory::Get("http://localhost:8086?db=R2H_Flight2&u=Lionel&p=Boxeur88&org=XSTRATO");
//    auto db = influxdb::InfluxDBFactory::Get("http://Lionel:Boxeur88@localhost:8086?db=R2H_Flight2");
    auto db = influxdb::InfluxDBFactory::Get("http://localhost:8086?bucket=R2H_Flight2XX&org=XSTRATO&token=mAU0qSxYKxB5IGUSmYA2-A81llbagYJjoFSM-wJRQanijR3QBxqrZAZd4gd04HlC1RgqrKjd5x2gT5ICYTlOGQ==");
//    auto db = influxdb::InfluxDBFactory::Get("http://localhost:8086?db=R2H_Flight2&org=XSTRATO", "mAU0qSxYKxB5IGUSmYA2-A81llbagYJjoFSM-wJRQanijR3QBxqrZAZd4gd04HlC1RgqrKjd5x2gT5ICYTlOGQ==");
//    db->createDatabaseIfNotExists();
    db->write(influxdb::Point{"temperature"}.addTag("city","DALLAS").addTag("device","companyX").addField("value",28));
//    for (auto i: db->query("SHOW DATABASES")) std::cout << i.getTags() << std::endl;
    return 0;
}
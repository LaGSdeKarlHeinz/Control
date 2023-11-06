# make sure no other process are running
sudo pkill influxd
sudo pkill grafana
# start new service
sudo influxd &
sudo grafana-server -homepath /usr/share/grafana &

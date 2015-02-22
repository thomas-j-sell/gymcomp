require 'rake'

phone = 'iPhsidus' # could be hostname or ip address

task :default => [:run]

desc "Builds and installs pebble app to watch, and then starts watching logs"
task :run do
  cmd = "pebble build && "
  cmd += "pebble install --phone #{phone}"
  sh cmd
  sleep 1 # wait for install connection to end before connecting with logs
  cmd = "pebble logs --phone #{phone}"
  sh cmd
end
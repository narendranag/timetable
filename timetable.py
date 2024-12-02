from datetime import datetime, timedelta
import pytz

def main():
    # Define the time zones and their labels
    time_zones = {
        "US West Coast": "US/Pacific",
        "US Central": "US/Central",
        "US East Coast": "US/Eastern",
        "Poland": "Europe/Warsaw",
        "India": "Asia/Kolkata",
    }

    # Create the start and end times for the table in UTC
    start_time = datetime(2023, 1, 1, 0, 0, 0, tzinfo=pytz.utc)
    end_time = datetime(2023, 1, 1, 12, 0, 0, tzinfo=pytz.utc)

    # Generate the table
    current_time = start_time
    time_table = []

    while current_time <= end_time:
        row = [current_time.strftime("%I:%M %p")]
        for label, tz_name in time_zones.items():
            local_time = current_time.astimezone(pytz.timezone(tz_name))
            row.append(local_time.strftime("%I:%M %p"))
        time_table.append(row)
        current_time += timedelta(minutes=30)

    # Print the table
    header = ["UTC"] + list(time_zones.keys())
    print("{:<10} {:<15} {:<15} {:<15} {:<10} {:<10}".format(*header))
    for row in time_table:
        print("{:<10} {:<15} {:<15} {:<15} {:<10} {:<10}".format(*row))

if __name__ == "__main__":
    main()

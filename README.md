# PodcastFeed
Podcast Player using RSS Feeds to keep track of Podcasts.

Using Qt to develop a program that allows the user to keep up with their favorite podcasts. The user enters an link to the iTunes/RSS podcast page. The program will remember the link, and fetch the xml data for the podcast into the users Documents directory. The user interface will have three panes below an audio player. The right most pane is context sensitive and will change based on what the user selects in the other two panes.

The left most pane will show the following (all read from the XML file):
* Podcast name
* Podcast artwork/logo
* Explicit/Not-Explicit

When a user left clicks the podcast name, the application will populate the middle pane with the list of episodes for the selected podcast. Additionally, the third pane will display additional information about the podcast that the user may find of use (name, author, number of episodes and description). The middle pane will show all the episodes of a podcast the user has selected in the left pane. It will also highlight any episodes the user has not already listened to. 

If the user clicks on an episode in the middle pane, the right pane is populated with information about the specific episode (podcast name, episode name/number, episode description, episode runtime, episode partly listened to/fully listened to). If there are any links in the description, the user will be able to click them and the application will open them using the systems default web browser.

The media player will have standard play/pause buttons, a label showing the current playing time of the episode. The user will be able to seek the playing of the file forward and backwards using a slider widget. There will also be two buttons for skipping forward and backwards by 15 seconds.

### Possible Additional Features: ###
* Allow for taking notes related to a specific podcast episode.
* Background Playback when user interface is closed (application goes to the taskbar.)

### Illustration: ###
![picture alt](https://github.com/ForeEyes/PodcastFeed/blob/master/readme%20illustration/Illustration.PNG)
![picture alt](https://github.com/ForeEyes/PodcastFeed/blob/master/readme%20illustration/Current_View.PNG)

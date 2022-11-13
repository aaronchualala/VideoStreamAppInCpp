# Simple Qt desktop application for three video streams

## Description
Displays from:
<ul>
    <li>Real-time device camera stream</li>
    <li>Online "Big Buck Bunny" stream</li>
    <li>Local "Al Jazeera" news clip</li>
</ul>

## Components
<ol>
    <li>Main - standard entry point to run program</li>
    <li>MainWindow - the window that instantiates and arranges all three QLabel displays and Stream objects, and connects their signals and slots</li>
    <li>Stream - a QThread that is instantiated with one of the above sources, reads frame from the source, and converts frame to appropriate format for subsequent display</li>
</ol>

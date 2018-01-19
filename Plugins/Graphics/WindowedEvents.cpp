//Basic events for keeping the window responcive and reacting as desired

// "close requested" event: we close the window
if (event.type == sf::Event::Closed)
{
    manager->kill();
    window->close();
}

// catch the resize events
if (event.type == sf::Event::Resized)
{
    //scale view to new window size
    sf::View view = sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height));
    //set center to old center
    view.setCenter(window->getView().getCenter());
    //propogate
    window->setView(view);
}

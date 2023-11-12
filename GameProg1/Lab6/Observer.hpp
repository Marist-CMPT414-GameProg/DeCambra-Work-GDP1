#ifndef HPP_OBSERVER
#define HPP_OBSERVER

/// <summary>
/// Interface for objects that watch for changes to another object.
/// </summary>
/// <typeparam name="E">indicates the type of Event data received</typeparam>
template <typename E>
class Observer {
public:
    /// <summary>
    /// Respond to a notification from the subject under observation.
    /// </summary>
    /// <param name="ev">information about what happened to the subject</param>
    virtual void onNotify(E const&) = 0;
};

#endif HPP_OBSERVER

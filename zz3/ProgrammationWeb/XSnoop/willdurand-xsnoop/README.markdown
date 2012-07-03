XSnoop
======

Reinvent the wheel in Java! This is a web application I wrote from scratch as an academic project, not really awesome but explain some stuffs
arround the **Front Controller Pattern**, the **Model View Controller**, and so on.


What's inside?
--------------

[Twitter Bootstrap](http://twitter.github.com/bootstrap/) is used as main CSS Framework + UI.

I added JSP blocks inheritance thanks to the rapid-framework tags. I love to write:

``` jsp
// layout.jsp
<div class="content">
    <div class="page-header">
        <in:block name="page-header"></in:block>
    </div>
    <in:block name="content"></in:block>
</div>
```

``` jsp
// index/index.jsp
<%@ include file="../layout.jsp" %>

<in:override name="page-header">
</in:override>

<in:override name="content">
    Some content
</in:override>
```

Quite funny isn't it?

I also added a basic routing _a la Symfony2_:

    /pages/<controller>/<action>?foo=bar

For instance, the following URI `/pages/index/index` will call the `indexAction()` method of the `IndexController`.

There is a kind of convention here. Each controller has to implement the `ControllerInterface`, as well as to be located in the
subpackage (`impl`). Each method as to be suffixed by `Action`, and each controller as to be suffixed by `Controller`.

This is the same convention for views:

```
views
    \_ index
    | |_ index.jsp
    | |_ step2.jsp
    |
    |_ foo
```

You can deal with `formats` too. For example, if you have a URL like `/pages/index/data`, you'll get the **HTML** response,
as well as you fetch `/pages/index/data.html`. But if you fetch `/pages/index/data.json`, then you'll be able to get the **JSON** response.
There is no magic here, I mean you have to do the job yourself, but it's quite easy to know the format: `request.getFormat()`.

Exceptions are named and all HTTP related exceptions should implement the `ExceptionInterface` interface.


Screenshots
-----------

![](https://github.com/willdurand/xsnoop/raw/master/doc/screenshot.png)

![](https://github.com/willdurand/xsnoop/raw/master/doc/screenshot2.png)


How to use it?
--------------

Just cherry-pick the `dist/xsnoop.war`, and put it in your favorite application server (GlassFish, Tomcat, JBoss, ...).


Dependencies / Credits
----------------------

This project depends on the following libraries:

* commons-lang3-3.1

I also included few classes from the [rapid-framework](http://rapid-framework.googlecode.com/svn/trunk/rapid-framework/).

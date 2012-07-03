package fr.isima.xsnoop.request;

import fr.isima.xsnoop.user.User;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.HttpSession;

/**
 * @author William Durand <william.durand1@gmail.com>
 */
public final class HttpServletRequest implements ServletRequest {

    /**
     * Formats
     */
    final static public String FORMAT_HTML      = "html";
    final static public String FORMAT_JSON      = "json";

    final static public String DEFAULT_FORMAT   = FORMAT_HTML;

    /**
     * HTTP verbs
     */
    final static public String POST = "POST";
    final static public String GET  = "GET";

    /**
     * Original request
     */
    private javax.servlet.http.HttpServletRequest request;

    /**
     * Format
     */
    private String format;

    public HttpServletRequest(javax.servlet.http.HttpServletRequest request) {
        this.request = request;

        if (getSession(true).getAttribute("errors") == null) {
            getSession(true).setAttribute("errors", new ArrayList<String>());
        }
        if (getSession(true).getAttribute("infos") == null) {
            getSession(true).setAttribute("infos",  new ArrayList<String>());
        }
    }

    /**
     * Add a message error
     * @param String message A message
     */
    public void addError(String message) {
        ((List<String>) getSession(true).getAttribute("errors")).add(message);
    }

    public List<String> getErrors() {
        return ((List<String>) getSession(true).getAttribute("errors"));
    }

    public void addInfo(String message) {
        ((List<String>) getSession(true).getAttribute("infos")).add(message);
    }

    public List<String> getInfos() {
        return ((List<String>) getSession(true).getAttribute("infos"));
    }

    public void setFormat(String format) {
        this.format = format;
    }

    public String getFormat() {
        return format;
    }

    public boolean isPost() {
        return request.getMethod().equals(POST);
    }

    public boolean isGet() {
        return request.getMethod().equals(GET);
    }

    public String getPathInfo() {
        return request.getPathInfo();
    }

    public String getMethod() {
        return request.getMethod();
    }

    public ServletRequest getRequest() {
        return request;
    }

    public HttpSession getSession(boolean b) {
        return request.getSession(b);
    }

    /**
     * Whether the user is authenticated or not, based on the request session.
     *
     * @param HttpServletRequest request    The request.
     * @return  boolean
     */
    public boolean isAuthenticated() {
        return null != getUser();
    }

    public User getUser() {
        return (User) getSession(false).getAttribute("user");
    }

    @Override
    public Object getAttribute(String name) {
        return request.getAttribute(name);
    }

    @Override
    public Enumeration<String> getAttributeNames() {
        return request.getAttributeNames();
    }

    @Override
    public String getCharacterEncoding() {
        return request.getCharacterEncoding();
    }

    @Override
    public void setCharacterEncoding(String env) throws UnsupportedEncodingException {
        request.setCharacterEncoding(env);
    }

    @Override
    public int getContentLength() {
        return request.getContentLength();
    }

    @Override
    public String getContentType() {
        return request.getContentType();
    }

    @Override
    public ServletInputStream getInputStream() throws IOException {
        return request.getInputStream();
    }

    @Override
    public String getParameter(String name) {
        return request.getParameter(name);
    }

    @Override
    public Enumeration<String> getParameterNames() {
        return request.getParameterNames();
    }

    @Override
    public String[] getParameterValues(String name) {
        return request.getParameterValues(name);
    }

    @Override
    public Map<String, String[]> getParameterMap() {
        return request.getParameterMap();
    }

    @Override
    public String getProtocol() {
        return request.getProtocol();
    }

    @Override
    public String getScheme() {
        return request.getScheme();
    }

    @Override
    public String getServerName() {
        return request.getServerName();
    }

    @Override
    public int getServerPort() {
        return request.getServerPort();
    }

    @Override
    public BufferedReader getReader() throws IOException {
        return request.getReader();
    }

    @Override
    public String getRemoteAddr() {
        return request.getRemoteAddr();
    }

    @Override
    public String getRemoteHost() {
        return request.getRemoteHost();
    }

    @Override
    public void setAttribute(String name, Object o) {
        request.setAttribute(name, o);
    }

    @Override
    public void removeAttribute(String name) {
        request.removeAttribute(name);
    }

    @Override
    public Locale getLocale() {
        return request.getLocale();
    }

    @Override
    public Enumeration<Locale> getLocales() {
        return request.getLocales();
    }

    @Override
    public boolean isSecure() {
        return request.isSecure();
    }

    @Override
    public RequestDispatcher getRequestDispatcher(String path) {
        return request.getRequestDispatcher(path);
    }

    @Override
    public String getRealPath(String path) {
        return request.getRealPath(path);
    }

    @Override
    public int getRemotePort() {
        return request.getRemotePort();
    }

    @Override
    public String getLocalName() {
        return request.getLocalName();
    }

    @Override
    public String getLocalAddr() {
        return request.getLocalAddr();
    }

    @Override
    public int getLocalPort() {
        return request.getLocalPort();
    }

    @Override
    public ServletContext getServletContext() {
        return request.getServletContext();
    }

    @Override
    public AsyncContext startAsync() throws IllegalStateException {
        return request.startAsync();
    }

    @Override
    public AsyncContext startAsync(ServletRequest servletRequest, ServletResponse servletResponse) throws IllegalStateException {
        return request.startAsync(servletRequest, servletResponse);
    }

    @Override
    public boolean isAsyncStarted() {
        return request.isAsyncStarted();
    }

    @Override
    public boolean isAsyncSupported() {
        return request.isAsyncSupported();
    }

    @Override
    public AsyncContext getAsyncContext() {
        return request.getAsyncContext();
    }

    @Override
    public DispatcherType getDispatcherType() {
        return request.getDispatcherType();
    }
}
